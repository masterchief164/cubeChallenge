import * as THREE from 'three';
import {OrbitControls} from 'three/examples/jsm/controls/OrbitControls';
import './style.css';
import raw from './outputs/3/33.txt';

const scene = new THREE.Scene();

let grid: boolean[][][] = [];
let n: number;

let camera: THREE.PerspectiveCamera;
let renderer: THREE.WebGLRenderer;
let controls: OrbitControls;

const readMatrix = async () => {
  const response = await fetch(raw);
  const text = await response.text();
  const lines = text.split('\n').filter((line) => line.length > 0);
  n = parseInt(lines[0]);
  lines.shift();
  const matrix = [];
  let layer = [];
  for (let i = 0; i < lines.length; i++) {
    const line = lines[i];
    if (i % n === 0) {
      matrix.push(layer);
      layer = [];
    }
    const elements = line.split(' ');
    const row = elements.map((element) => element === '1');
    layer.push(row);
  }
  matrix.push(layer);
  matrix.shift();
  return matrix;
}

const init = (n: number) => {
  const geometry = new THREE.BoxGeometry(1, 1, 1);
  const material = new THREE.MeshStandardMaterial({color: 0x00ff83});
  const transparentMaterial = new THREE.MeshStandardMaterial({color: 0x002f83, transparent: true, opacity: 0});

  const geo = new THREE.EdgesGeometry(geometry);
  const mat = new THREE.LineBasicMaterial({color: 0xffffff, transparent: true, opacity: 0.1});
  const wireframe = new THREE.LineSegments(geo, mat);


  for (let i = 0; i < n; i++) {
    for (let j = 0; j < n; j++) {
      for (let k = 0; k < n; k++) {
        if (grid[i][j][k]) {
          const cube = new THREE.Mesh(geometry, material);
          cube.position.set(i, j, k);
          wireframe.position.set(i, j, k);
          scene.add(wireframe.clone());
          cube.material.transparent = grid[i][j][k];
          cube.material.opacity = 1;
          scene.add(cube);
        } else {
          const cube = new THREE.Mesh(geometry, transparentMaterial);
          cube.position.set(i, j, k);
          wireframe.position.set(i, j, k);
          scene.add(wireframe.clone());
          cube.material.transparent = grid[i][j][k];
          cube.material.opacity = 0.5;
          cube.visible = false;
          scene.add(cube);
        }
      }
    }
  }


  const sizes = {
    width: window.innerWidth,
    height: window.innerHeight
  }

  camera = new THREE.PerspectiveCamera(45, sizes.width / sizes.height, 0.1, 1000);
  camera.position.z = 7 * Math.sqrt(n);
  camera.position.x = 7 * Math.sqrt(n);
  camera.position.y = 7 * Math.sqrt(n);
  scene.add(camera);

  const light = new THREE.PointLight(0xffffff, 1);
  light.position.set(10, 10, 10);
  scene.add(light);

  const light2 = new THREE.PointLight(0xffffff, 1);
  light2.position.set(-10, -10, -10);
  scene.add(light2);


  const canvas = document.querySelector('.webgl') as HTMLCanvasElement;

  renderer = new THREE.WebGLRenderer({canvas});
  renderer.setPixelRatio(window.devicePixelRatio);
  renderer.setSize(sizes.width, sizes.height);
  renderer.render(scene, camera);
  renderer.sortObjects = false;


  controls = new OrbitControls(camera, canvas);
  controls.enableDamping = true;
  // controls.autoRotate = true;
  // controls.autoRotateSpeed = 0.5;

  window.addEventListener('resize', () => {
    sizes.width = window.innerWidth;
    sizes.height = window.innerHeight;

    camera.aspect = sizes.width / sizes.height;
    camera.updateProjectionMatrix();
    renderer.setSize(sizes.width, sizes.height);
  });

}

const loop = () => {
  controls.update();
  renderer.render(scene, camera);
  window.requestAnimationFrame(loop);
}


readMatrix().then((matrix) => {
  grid = matrix;
  init(n);
  loop();
});
