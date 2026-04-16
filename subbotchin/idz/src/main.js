import * as THREE from 'three';

import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';
import { HDRLoader } from 'three/addons/loaders/HDRLoader.js';

let scene, renderer, camera, floor, orbitControls;
let group, followGroup, model, skeleton, mixer, timer;
let bulbLight;

let walkAction;
let points = 0;
let bulbMesh;

const PI = Math.PI;
const PI90 = Math.PI / 2;

const raycaster = new THREE.Raycaster();
const mouse = new THREE.Vector2();

const controls = {

	key: [ 0, 0 ],
	ease: new THREE.Vector3(),
	position: new THREE.Vector3(),
	up: new THREE.Vector3( 0, 1, 0 ),
	rotate: new THREE.Quaternion(),
	isWalking: false,
	isMovingToTarget: false,
	walkVelocity: 0.6,
	rotateSpeed: 0.027,
	floorDecale: 0,
	targetPosition: null,

};


init();

function init() {

	const container = document.getElementById( 'container' );

	camera = new THREE.PerspectiveCamera( 45, window.innerWidth / window.innerHeight, 0.1, 100 );
	camera.position.set( 0, 5, - 5 );

	timer = new THREE.Timer();
	timer.connect( document );

	scene = new THREE.Scene();
	scene.background = new THREE.Color( 0x5e5d5d );
	scene.fog = new THREE.Fog( 0x5e5d5d, 2, 20 );

	group = new THREE.Group();
	scene.add( group );

	followGroup = new THREE.Group();
	scene.add( followGroup );

	const dirLight = new THREE.DirectionalLight( 0xffffff, 5 );
	dirLight.position.set( - 2, 5, - 3 );
	dirLight.castShadow = false;
	followGroup.add( dirLight );
	followGroup.add( dirLight.target );

	renderer = new THREE.WebGLRenderer( { antialias: true } );
	renderer.setPixelRatio( window.devicePixelRatio );
	renderer.setSize( window.innerWidth, window.innerHeight );
	renderer.setAnimationLoop( animate );
	renderer.toneMapping = THREE.ACESFilmicToneMapping;
	renderer.toneMappingExposure = 0.5;
	renderer.shadowMap.enabled = true;
	renderer.shadowMap.type = THREE.PCFShadowMap;
	container.appendChild( renderer.domElement );

	orbitControls = new OrbitControls( camera, renderer.domElement );
	orbitControls.target.set( 0, 1, 0 );
	orbitControls.enableDamping = true;
	orbitControls.enablePan = false;
	orbitControls.maxPolarAngle = PI90 - 0.05;
	orbitControls.update();

	// EVENTS

	window.addEventListener( 'resize', onWindowResize );
	document.addEventListener( 'keydown', onKeyDown );
	document.addEventListener( 'keyup', onKeyUp );
	window.addEventListener( 'mousedown', onMouseDown );
	renderer.domElement.addEventListener( 'contextmenu', ( e ) => e.preventDefault() );


	// DEMO

	new HDRLoader()
		.setPath( '../assets/textures/equirectangular/' )
		.load( 'lobe.hdr', function ( texture ) {

			texture.mapping = THREE.EquirectangularReflectionMapping;
			scene.environment = texture;
			scene.environmentIntensity = 1.5;

			loadModel();
			addFloor();

		} );

}

function addFloor() {

	const size = 64;
	const repeat = 64;

	const maxAnisotropy = renderer.capabilities.getMaxAnisotropy();

	const floorT = new THREE.TextureLoader().load( '../assets/textures/floors/FloorsCheckerboard_S_Diffuse.jpg' );
	floorT.colorSpace = THREE.SRGBColorSpace;
	floorT.repeat.set( repeat, repeat );
	floorT.wrapS = floorT.wrapT = THREE.RepeatWrapping;
	floorT.anisotropy = maxAnisotropy;

	const floorN = new THREE.TextureLoader().load( '../assets/textures/floors/FloorsCheckerboard_S_Normal.jpg' );
	floorN.repeat.set( repeat, repeat );
	floorN.wrapS = floorN.wrapT = THREE.RepeatWrapping;
	floorN.anisotropy = maxAnisotropy;

	const mat = new THREE.MeshStandardMaterial( { map: floorT, normalMap: floorN, normalScale: new THREE.Vector2( 0.5, 0.5 ), color: 0x404040, depthWrite: false, roughness: 0.85 } );

	const g = new THREE.PlaneGeometry( size, size, 50, 50 );
	g.rotateX( - PI90 );

	floor = new THREE.Mesh( g, mat );
	floor.receiveShadow = true;
	scene.add( floor );

	controls.floorDecale = ( size / repeat ) * 4;

	createBulb();

}

function loadModel() {

	const loader = new GLTFLoader();
	loader.load( '../assets/models/duck_walk_free/scene.gltf', function ( gltf ) {

		model = gltf.scene;
		group.add( model );
		model.rotation.y = 0;
		group.rotation.y = 0;

		model.traverse( function ( object ) {

			if ( object.isMesh ) {

				object.castShadow = true;
				object.receiveShadow = true;
				object.material.metalness = 0.7;
				object.material.roughness = 0.6;
				object.material.color.set( 1, 1, 1 );
				object.material.metalnessMap = object.material.map;

			}

		} );

		//

		skeleton = new THREE.SkeletonHelper( model );
		skeleton.setColors( new THREE.Color( 0xe000ff ), new THREE.Color( 0x00e0ff ) );
		skeleton.visible = false;
		scene.add( skeleton );

		const animations = gltf.animations;

		mixer = new THREE.AnimationMixer( model );

		if ( animations.length > 0 ) {

			walkAction = mixer.clipAction( animations[ 0 ] );
			walkAction.enabled = true;
			walkAction.setEffectiveTimeScale( 1 );
			walkAction.setEffectiveWeight( 0 );

		}

		animate();

	} );

}

function updateCharacter( delta ) {

	const key = controls.key;
	const up = controls.up;
	const ease = controls.ease;
	const rotate = controls.rotate;
	const position = controls.position;
	const azimuth = orbitControls.getAzimuthalAngle();

	const isMoving = key[ 0 ] !== 0 || key[ 1 ] !== 0;

	// If keyboard is pressed and duck is moving to target, clear target
	if ( isMoving && controls.isMovingToTarget ) {
		controls.targetPosition = null;
		controls.isMovingToTarget = false;
	}

	// Play or stop walk animation
	if ( ( isMoving || controls.isMovingToTarget ) && !controls.isWalking ) {

		if ( walkAction ) {
			walkAction.setEffectiveWeight( 1 );
			walkAction.play();
		}
		controls.isWalking = true;

	} else if ( !isMoving && !controls.isMovingToTarget && controls.isWalking ) {

		if ( walkAction ) {
			walkAction.setEffectiveWeight( 0 );
			walkAction.stop();
		}
		controls.isWalking = false;

	}

	// move object

	if ( isMoving ) {

		// walk velocity
		ease.set( key[ 1 ], 0, key[ 0 ] ).multiplyScalar( controls.walkVelocity * delta );

		// calculate camera direction
		const angle = unwrapRad( Math.atan2( ease.x, ease.z ) + azimuth );
		rotate.setFromAxisAngle( up, angle );

		// apply camera angle on ease
		controls.ease.applyAxisAngle( up, azimuth );

		position.add( ease );
		camera.position.add( ease );

		group.position.copy( position );
		group.quaternion.rotateTowards( rotate, controls.rotateSpeed );

		orbitControls.target.copy( position ).add( { x: 0, y: 1, z: 0 } );
		followGroup.position.copy( position );

		// Move the floor without any limit
		const dx = ( position.x - floor.position.x );
		const dz = ( position.z - floor.position.z );
		if ( Math.abs( dx ) > controls.floorDecale ) floor.position.x += dx;
		if ( Math.abs( dz ) > controls.floorDecale ) floor.position.z += dz;

	} else if ( controls.isMovingToTarget && controls.targetPosition ) {

		// Move towards target
		const direction = new THREE.Vector3().subVectors( controls.targetPosition, position ).normalize();
		ease.copy( direction ).multiplyScalar( controls.walkVelocity * delta );

		// Calculate angle to target
		const angle = unwrapRad( Math.atan2( direction.x, direction.z ) );
		rotate.setFromAxisAngle( up, angle );

		// Check if reached target (within small threshold)
		const distanceToTarget = position.distanceTo( controls.targetPosition );
		if ( distanceToTarget < 0.2 ) {
			controls.targetPosition = null;
			controls.isMovingToTarget = false;
		} else {
			position.add( ease );
			camera.position.add( ease );

			group.position.copy( position );
			group.quaternion.rotateTowards( rotate, controls.rotateSpeed );

			orbitControls.target.copy( position ).add( { x: 0, y: 1, z: 0 } );
			followGroup.position.copy( position );

			// Move the floor without any limit
			const dx = ( position.x - floor.position.x );
			const dz = ( position.z - floor.position.z );
			if ( Math.abs( dx ) > controls.floorDecale ) floor.position.x += dx;
			if ( Math.abs( dz ) > controls.floorDecale ) floor.position.z += dz;
		}

	}

	if ( mixer ) mixer.update( delta );

	orbitControls.update();

}

function unwrapRad( r ) {

	return Math.atan2( Math.sin( r ), Math.cos( r ) );

}

function createBulb() {

	if ( !bulbLight ) {
		const bulbGeometry = new THREE.SphereGeometry( 0.05, 16, 8 );
		bulbLight = new THREE.PointLight( 0xffee88, 5, 500, 1 );

		const bulbMat = new THREE.MeshStandardMaterial( { emissive: 0xffffee, emissiveIntensity: 2, color: 0x000000 } );
		bulbMesh = new THREE.Mesh( bulbGeometry, bulbMat );
		bulbLight.add( bulbMesh );
		
		bulbLight.castShadow = true;
		bulbLight.shadow.mapSize.set( 512, 512 );
		bulbLight.shadow.camera.near = 0.1;
		bulbLight.shadow.camera.far = 15;
		scene.add( bulbLight );
	}
	const randomX = controls.position.x + ( Math.random() - 0.5 ) * 10;
	const randomZ = controls.position.z + ( Math.random() - 0.5 ) * 10;
	bulbLight.position.set( randomX, 0.3, randomZ );
}

function checkCollisionWithBulb() {

	if ( ! bulbLight ) return;

	const charPos = group.position;
	const bulbPos = bulbLight.position;
	const distance = charPos.distanceTo( bulbPos );

	if ( distance < 0.5 ) {

		points += 1;
		document.getElementById( 'score' ).textContent = points;
		createBulb();

	}

}

function onKeyDown( event ) {

	const key = controls.key;
	switch ( event.code ) {

		case 'ArrowUp': case 'KeyW': case 'KeyZ': 
			key[ 0 ] = - 1; 
			if ( controls.isMovingToTarget ) {
				controls.targetPosition = null;
				controls.isMovingToTarget = false;
			}
			break;
		case 'ArrowDown': case 'KeyS': 
			key[ 0 ] = 1;
			if ( controls.isMovingToTarget ) {
				controls.targetPosition = null;
				controls.isMovingToTarget = false;
			}
			break;
		case 'ArrowLeft': case 'KeyA': case 'KeyQ': 
			key[ 1 ] = - 1;
			if ( controls.isMovingToTarget ) {
				controls.targetPosition = null;
				controls.isMovingToTarget = false;
			}
			break;
		case 'ArrowRight': case 'KeyD': 
			key[ 1 ] = 1;
			if ( controls.isMovingToTarget ) {
				controls.targetPosition = null;
				controls.isMovingToTarget = false;
			}
			break;

	}

}

function onKeyUp( event ) {

	const key = controls.key;
	switch ( event.code ) {

		case 'ArrowUp': case 'KeyW': case 'KeyZ': key[ 0 ] = key[ 0 ] < 0 ? 0 : key[ 0 ]; break;
		case 'ArrowDown': case 'KeyS': key[ 0 ] = key[ 0 ] > 0 ? 0 : key[ 0 ]; break;
		case 'ArrowLeft': case 'KeyA': case 'KeyQ': key[ 1 ] = key[ 1 ] < 0 ? 0 : key[ 1 ]; break;
		case 'ArrowRight': case 'KeyD': key[ 1 ] = key[ 1 ] > 0 ? 0 : key[ 1 ]; break;

	}

}

function onWindowResize() {

	camera.aspect = window.innerWidth / window.innerHeight;
	camera.updateProjectionMatrix();
	renderer.setSize( window.innerWidth, window.innerHeight );

}

function onMouseDown( event ) {

	// Right click sets target position
	if ( event.button === 2 ) {

		// Prevent context menu
		event.preventDefault();

		// Calculate mouse position in normalized device coordinates
		const rect = renderer.domElement.getBoundingClientRect();
		mouse.x = ( ( event.clientX - rect.left ) / rect.width ) * 2 - 1;
		mouse.y = - ( ( event.clientY - rect.top ) / rect.height ) * 2 + 1;

		// Update the picking ray with the camera and mouse position
		raycaster.setFromCamera( mouse, camera );

		// Calculate objects intersecting the picking ray
		const intersects = raycaster.intersectObject( floor );

		if ( intersects.length > 0 ) {

			const point = intersects[ 0 ].point;
			controls.targetPosition = new THREE.Vector3( point.x, controls.position.y, point.z );
			controls.isMovingToTarget = true;

		}

	}

}

function animate() {

	timer.update();

	// Render loop

	const delta = timer.getDelta();

	updateCharacter( delta );

	checkCollisionWithBulb();

	// Update position display
	document.getElementById( 'position' ).textContent = `X: ${controls.position.x.toFixed(1)} Z: ${controls.position.z.toFixed(1)}`;

	renderer.render( scene, camera );

}
