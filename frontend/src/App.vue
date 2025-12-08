<template>
  <q-layout view="hHh lpR fFf">
    <q-header elevated class="bg-primary text-white">
      <q-toolbar>
        <q-toolbar-title>
          <q-avatar>
            <img src="https://cdn.quasar.dev/logo-v2/svg/logo-mono-white.svg">
          </q-avatar>
          Pixel Art Tool
        </q-toolbar-title>
      </q-toolbar>
    </q-header>

    <q-page-container>
      <q-page class="flex flex-center bg-grey-2">
        <PixelEditor />
      </q-page>
    </q-page-container>
  </q-layout>
</template>

<script setup lang="ts">
import PixelEditor from './components/PixelEditor.vue';
</script>