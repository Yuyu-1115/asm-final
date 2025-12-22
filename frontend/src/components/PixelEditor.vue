<template>
  <div class="pixel-editor-container q-pa-md">
    <q-card class="my-card" flat bordered>
      <q-card-section>
        <div class="text-h6">Pixel Art Editor</div>
      </q-card-section>

      <q-card-section class="row q-col-gutter-md">
        <!-- Canvas Area -->
        <div class="col-12 col-md-8 flex flex-center canvas-wrapper">
          <canvas
            ref="canvasRef"
            :width="width"
            :height="height"
            class="pixel-canvas"
            @mousedown="startDrawing"
            @mousemove="draw"
            @mouseup="stopDrawing"
            @mouseleave="stopDrawing"
          ></canvas>
        </div>

        <!-- Controls Area -->
        <div class="col-12 col-md-4">
          <div class="q-gutter-y-md">
            <!-- Color Picker -->
            <q-color v-model="currentColor" format-model="hex" no-header no-footer class="my-color-picker" />

            <!-- RGB Inputs -->

                        <div class="row q-gutter-sm no-wrap">

                          <q-input

                            v-model.number="red"

                            type="number"

                            label="R"

                            outlined

                            dense

                            min="0"

                            max="255"

                            :rules="[val => (val >= 0 && val <= 255) || '0-255']"

                            @update:model-value="updateCurrentColorFromRgb"

                          />

                          <q-input

                            v-model.number="green"

                            type="number"

                            label="G"

                            outlined

                            dense

                            min="0"

                            max="255"

                            :rules="[val => (val >= 0 && val <= 255) || '0-255']"

                            @update:model-value="updateCurrentColorFromRgb"

                          />

                          <q-input

                            v-model.number="blue"

                            type="number"

                            label="B"

                            outlined

                            dense

                            min="0"

                            max="255"

                            :rules="[val => (val >= 0 && val <= 255) || '0-255']"

                            @update:model-value="updateCurrentColorFromRgb"

                          />

                        </div>

                        <q-separator />

                        <!-- Preset Palette -->

                        <div class="text-subtitle2 q-mt-md">Preset Palette</div>

                        <div class="preset-palette">

                          <div

                            v-for="color in presetPalette"

                            :key="color"

                            class="swatch"

                            :style="{ backgroundColor: color }"

                            @click="currentColor = color"

                          ></div>

                        </div>

                      </div>

                    </div>

                  </q-card-section>

                </q-card>

              </div>

            </template>

            

            <script setup lang="ts">

            import { ref, onMounted, watch } from 'vue';

            import { parsePPM, toPPM } from '../utils/ppm';

            import { useQuasar } from 'quasar';

            

            const props = defineProps<{

              initialTool: 'pencil' | 'fill' | 'eraser';

              artId: number | null;

              loading: boolean;

            }>();

            

            const emit = defineEmits(['update:artId', 'update:loading']);

            

            const $q = useQuasar();

            

            const API_BASE_URL = 'http://localhost:8080';

            

            const width = 64;

            const height = 64;

            

            const canvasRef = ref<HTMLCanvasElement | null>(null);

            const ctx = ref<CanvasRenderingContext2D | null>(null);

            

            const currentColor = ref('#000000');

            const currentTool = ref(props.initialTool);

            const isDrawing = ref(false);

            const lastPos = ref<{ x: number; y: number } | null>(null);

            

            const presetPalette = [

              '#2e222f', '#3e3546', '#625565', '#966c6c', '#ab947a', '#694f62', '#7f708a', '#9babb2',

              '#c7dcd0', '#ffffff', '#6e2727', '#b33831', '#ea4f36', '#f57d4a', '#ae2334', '#e83b3b',

              '#fb6b1d', '#f79617', '#f9c22b', '#7a3045', '#9e4539', '#cd683d', '#e6904e', '#fbb954',

              '#4c3e24', '#676633', '#a2a947', '#d5e04b', '#fbff86', '#165a4c', '#239063', '#1ebc73',

              '#91db69', '#cddf6c', '#313638', '#374e4a', '#547e64', '#92a984', '#b2ba90', '#0b5e65',

              '#0b8a8f', '#0eaf9b', '#30e1b9', '#8ff8e2', '#323353', '#484a77', '#4d65b4', '#4d9be6',

              '#8fd3ff', '#45293f', '#6b3e75', '#905ea9', '#a884f3', '#eaaded', '#753c54', '#a24b6f',

              '#cf657f', '#ed8099', '#831c5d', '#c32454', '#f04f78', '#f68181', '#fca790', '#fdcbb0'

            ];

            

            // RGB inputs

            const red = ref(0);

            const green = ref(0);

            const blue = ref(0);

            

            // Helper to convert RGB to Hex

            const rgbToHex = (r: number, g: number, b: number) => {

              const toHex = (c: number) => `00${Math.max(0, Math.min(255, c)).toString(16)}`.slice(-2);

              return `#${toHex(r)}${toHex(g)}${toHex(b)}`.toUpperCase();

            };

            

            // Update currentColor from RGB inputs

            let updatingRgbFromHex = false; // Flag to prevent infinite loop

            

            const updateCurrentColorFromRgb = () => {

              if (updatingRgbFromHex) return;

              const newHex = rgbToHex(red.value, green.value, blue.value);

              if (currentColor.value !== newHex) {

                currentColor.value = newHex;

              }

            };

            

            

            watch(() => props.initialTool, (newVal) => {

              currentTool.value = newVal;

            });

            

            onMounted(() => {

              if (canvasRef.value) {

                ctx.value = canvasRef.value.getContext('2d', { willReadFrequently: true });

                clearCanvas();

              }

            });

            

            const hexToRgb = (hex: string) => {

              const result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);

              if (!result) return { r: 0, g: 0, b: 0 };

              return {

                r: parseInt(result[1]!, 16),

                g: parseInt(result[2]!, 16),

                b: parseInt(result[3]!, 16)

              };

            };

            

            // Watch currentColor to update RGB inputs

            watch(currentColor, (newHex) => {

              updatingRgbFromHex = true;

              const rgb = hexToRgb(newHex);

              red.value = rgb.r;

              green.value = rgb.g;

              blue.value = rgb.b;

              // Use a timeout to prevent the flag from being reset too early, which can cause issues with rapid color changes.

              setTimeout(() => {

                updatingRgbFromHex = false;

              }, 10);

            }, { immediate: true }); // immediate: true to set initial RGB values

            

            

            const getMousePos = (e: MouseEvent) => {

              if (!canvasRef.value) return { x: 0, y: 0 };

              const rect = canvasRef.value.getBoundingClientRect();

              const x = Math.floor((e.clientX - rect.left) / (rect.width / width));

              const y = Math.floor((e.clientY - rect.top) / (rect.height / height));

              return { x, y };

            };

            

            const startDrawing = (e: MouseEvent) => {

              isDrawing.value = true;

              const pos = getMousePos(e);

              lastPos.value = pos;

              draw(e);

            };

            

            const stopDrawing = () => {

              isDrawing.value = false;

              lastPos.value = null;

            };

            

            const plotLine = (x0: number, y0: number, x1: number, y1: number, color: string) => {

                if (!ctx.value) return;

                const dx = Math.abs(x1 - x0);

                const dy = Math.abs(y1 - y0);

                const sx = (x0 < x1) ? 1 : -1;

                const sy = (y0 < y1) ? 1 : -1;

                let err = dx - dy;

            

                ctx.value.fillStyle = color;

            

                while(true) {

                    ctx.value.fillRect(x0, y0, 1, 1);

                    if ((x0 === x1) && (y0 === y1)) break;

                    const e2 = 2 * err;

                    if (e2 > -dy) { err -= dy; x0 += sx; }

                    if (e2 < dx) { err += dx; y0 += sy; }

                }

            }

            

            const draw = (e: MouseEvent) => {

              if (!isDrawing.value && e.type !== 'click') return;

              if (!ctx.value) return;

            

              const { x, y } = getMousePos(e);

              

              if (x < 0 || x >= width || y < 0 || y >= height) {

                  lastPos.value = null; // Stop drawing if cursor leaves canvas

                  return;

              }

            

              if (currentTool.value === 'pencil') {

                if (lastPos.value) {

                    plotLine(lastPos.value.x, lastPos.value.y, x, y, currentColor.value);

                }

                lastPos.value = { x, y };

              } else if (currentTool.value === 'eraser') {

                if (lastPos.value) {

                    plotLine(lastPos.value.x, lastPos.value.y, x, y, '#FFFFFF');

                }

                lastPos.value = { x, y };

              } else if (currentTool.value === 'fill') {

                  floodFill(x, y, currentColor.value);

                  isDrawing.value = false; // Fill is a one-time action per click

              }

            };

            

            const getColorAt = (x: number, y: number) => {

                if (!ctx.value) return null;

                const imgData = ctx.value.getImageData(x, y, 1, 1);

                return {

                    r: imgData.data[0] ?? 0,

                    g: imgData.data[1] ?? 0,

                    b: imgData.data[2] ?? 0

                };

            }

            

            const colorsMatch = (c1: {r:number, g:number, b:number}, c2: {r:number, g:number, b:number}) => {

                return c1.r === c2.r && c1.g === c2.g && c1.b === c2.b;

            }

            

            const floodFill = (startX: number, startY: number, hexColor: string) => {

                if (!ctx.value) return;

                const targetColor = hexToRgb(hexColor);

                const startColor = getColorAt(startX, startY);

                if (!startColor) return;

                if (colorsMatch(targetColor, startColor)) return;

            

                const stack = [[startX, startY]];

                const w = width;

                const h = height;

            

                const imageData = ctx.value.getImageData(0, 0, w, h);

                const data = imageData.data;

            

                const getIdx = (x: number, y: number) => (y * w + x) * 4;

            

                const startR = startColor.r;

                const startG = startColor.g;

                const startB = startColor.b;

            

                while(stack.length > 0) {

                    const pop = stack.pop();

                    if(!pop) break;

                    const [x, y] = pop;

            

                    if (x === undefined || y === undefined) continue;

            

                    const idx = getIdx(x, y);

            

                    if (data[idx] === startR && data[idx+1] === startG && data[idx+2] === startB) {

                        data[idx] = targetColor.r;

                        data[idx+1] = targetColor.g;

                        data[idx+2] = targetColor.b;

                        data[idx+3] = 255;

            

                        if (x > 0) stack.push([x - 1, y]);

                        if (x < w - 1) stack.push([x + 1, y]);

                        if (y > 0) stack.push([x, y - 1]);

                        if (y < h - 1) stack.push([x, y + 1]);

                    }

                }

            

                ctx.value.putImageData(imageData, 0, 0);

            }

            

            

            const clearCanvas = () => {

              if (!ctx.value) return;

              ctx.value.fillStyle = '#FFFFFF';

              ctx.value.fillRect(0, 0, width, height);

            };

            

            // API Functions

            const loadArt = async () => {

              if (!props.artId) return;

              emit('update:loading', true);

              try {

                const res = await fetch(`${API_BASE_URL}/read?id=${props.artId}`);

                if (!res.ok) throw new Error('Failed to load');

                const text = await res.text();

                const result = parsePPM(text);

                if (result && ctx.value) {

                    const imgData = new ImageData(new Uint8ClampedArray(result.data), result.width, result.height);

                    ctx.value.putImageData(imgData, 0, 0);

                    $q.notify({ type: 'positive', message: 'Loaded successfully' });

                }

              } catch (e) {

                console.error(e);

                $q.notify({ type: 'negative', message: 'Failed to load art' });

              } finally {

                emit('update:loading', false);

              }

            };

            

            const downloadArt = () => {

                if(!props.artId) return;

                window.open(`${API_BASE_URL}/download?id=${props.artId}`, '_blank');

            };

            

            const saveArt = async () => {

                if (!ctx.value) return;

                emit('update:loading', true);

                try {

                    const imageData = ctx.value.getImageData(0, 0, width, height);

                    const ppm = toPPM(width, height, imageData.data);

                    

                    const res = await fetch(`${API_BASE_URL}/create`, {

                        method: 'POST',

                        headers: { 'Content-Type': 'text/plain' },

                        body: ppm

                    });

                    

                    if (!res.ok) throw new Error('Failed to create');

                    

                    let id;

                    try {

                        const json = await res.json();

                        id = json.id || json.art;

                    } catch (e) {

                        const val = res.headers.get('{"id"');

                        if (val) {

                            id = parseInt(val);

                        } else {

                            res.headers.forEach((hVal, hKey) => {

                               if (hKey.includes('"id"')) {

                                   const m = hVal.match(/\d+/);

                                   if (m) id = parseInt(m[0]);

                               }

                            });

                        }

                        if (!id) throw e;

                    }

                    

                    emit('update:artId', id);

                    

                    $q.dialog({

                      title: 'Art Created',

                      message: `Your new artwork has been saved with ID: ${id}`,

                      persistent: true

                    });

            

                } catch (e) {

                    console.error(e);

                    $q.notify({ type: 'negative', message: 'Failed to create art' });

                } finally {

                    emit('update:loading', false);

                }

            };

            

            const updateArt = async () => {

                if (!props.artId || !ctx.value) return;

                emit('update:loading', true);

                try {

                    const imageData = ctx.value.getImageData(0, 0, width, height);

                    const ppm = toPPM(width, height, imageData.data);

                    

                    const res = await fetch(`${API_BASE_URL}/update?id=${props.artId}`, {

                        method: 'POST',

                        headers: { 'Content-Type': 'text/plain' },

                        body: ppm

                    });

                    

                    if (!res.ok) throw new Error('Failed to update');

                    

                    $q.notify({ type: 'positive', message: 'Updated successfully' });

            

                } catch (e) {

                    console.error(e);

                    $q.notify({ type: 'negative', message: 'Failed to update art' });

                } finally {

                    emit('update:loading', false);

                }

            };

            

            defineExpose({

              loadArt,

              downloadArt,

              saveArt,

              updateArt,

              clearCanvas

            });

            </script>

            

            <style scoped>

            .pixel-canvas {

              border: 1px solid #ccc;

              image-rendering: pixelated;

              width: 512px;

              height: 512px;

              cursor: crosshair;

              background-color: white;

              box-shadow: 0 0 10px rgba(0,0,0,0.1);

            }

            

            .canvas-wrapper {

                background-color: #f0f0f0;

                padding: 20px;

                border-radius: 8px;

            }

            

            .my-color-picker {

                width: 100%;

                max-width: 250px;

            }

            

            .preset-palette {

              display: grid;

              grid-template-columns: repeat(auto-fill, minmax(20px, 1fr));

              gap: 4px;

              max-width: 250px;

            }

            

            .swatch {

              width: 20px;

              height: 20px;

              border-radius: 4px;

              cursor: pointer;

              border: 1px solid #ccc;

              transition: transform 0.1s ease;

            }

            

            .swatch:hover {

              transform: scale(1.1);

            }

            </style>

            