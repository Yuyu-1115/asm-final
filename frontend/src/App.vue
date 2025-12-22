<template>
  <q-layout view="hHh lpR fFf">
    <q-header elevated class="bg-primary text-white">
      <q-toolbar>
        <q-toolbar-title>
          <q-avatar>
            <img src="https://cdn.quasar.dev/logo-v2/svg/logo-mono-white.svg" />
          </q-avatar>
          Pixel Art Tool
        </q-toolbar-title>

        <q-space />

        <ToolbarActions
          :initial-art-id="artId"
          :initial-tool="tool"
          :loading="loading"
          @update:art-id="artId = $event"
          @update:tool="tool = $event"
          @load="pixelEditorRef?.loadArt()"
          @download="pixelEditorRef?.downloadArt()"
          @clear="pixelEditorRef?.clearCanvas()"
          @create="pixelEditorRef?.saveArt()"
          @update="pixelEditorRef?.updateArt()"
        />
      </q-toolbar>
    </q-header>

    <q-page-container>
      <q-page class="flex flex-center bg-grey-2">
        <PixelEditor
          ref="pixelEditorRef"
          :initial-tool="tool"
          v-model:art-id="artId"
          v-model:loading="loading"
        />
      </q-page>
    </q-page-container>
  </q-layout>
</template>

<script setup lang="ts">
import { ref } from 'vue';
import PixelEditor from './components/PixelEditor.vue';
import ToolbarActions from './components/ToolbarActions.vue';

const pixelEditorRef = ref<InstanceType<typeof PixelEditor> | null>(null);

const artId = ref<number | null>(null);
const tool = ref<'pencil' | 'fill' | 'eraser'>('pencil');
const loading = ref(false);
</script>