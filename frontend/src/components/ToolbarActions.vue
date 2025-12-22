<template>
  <div class="row items-center q-gutter-sm">
    <q-input dark dense standout v-model.number="artId" type="number" label="Art ID" class="q-ml-md" />
    <q-btn flat round dense icon="refresh" @click="$emit('load')" :disable="!artId" :loading="loading" />
    <q-btn flat round dense icon="file_download" @click="$emit('download')" :disable="!artId" :loading="loading" />

    <q-separator vertical inset dark />


    <q-btn flat :color="tool === 'pencil' ? 'grey' : 'white'" icon="brush" label="Pencil"
      @click="onToolChange('pencil')" />
    <q-btn flat :color="tool === 'fill' ? 'grey' : 'white'" icon="format_color_fill" label="Fill"
      @click="onToolChange('fill')" />
    <q-btn flat :color="tool === 'eraser' ? 'grey' : 'white'" icon="backspace" label="Eraser"
      @click="onToolChange('eraser')" />

    <q-separator vertical inset dark />

    <q-btn flat round dense icon="delete" @click="$emit('clear')" />

    <q-separator vertical inset dark />

    <q-btn color="secondary" icon="add" label="New" @click="$emit('create')" :loading="loading" />
    <q-btn color="primary" icon="save" label="Save" @click="$emit('update')" :loading="loading" />
  </div>
</template>

<script setup lang="ts">
import { computed, ref, watch } from 'vue';

const props = defineProps<{
  initialArtId: number | null;
  initialTool: 'pencil' | 'fill' | 'eraser';
  loading: boolean;
}>();

const emit = defineEmits(['update:artId', 'update:tool', 'load', 'download', 'clear', 'create', 'update']);

const artId = computed({
  get: () => props.initialArtId,
  set: (val: any) => {
    if (typeof val === 'string' && val.length > 0) {
      const parsed = parseInt(val, 10);
      if (!isNaN(parsed)) {
        emit('update:artId', parsed);
      }
    } else if (val === null || val === '') {
      emit('update:artId', null);
    } else if (typeof val === 'number') {
      emit('update:artId', val);
    }
  }
});
const tool = ref(props.initialTool);

watch(() => props.initialTool, (newVal) => {
  tool.value = newVal;
});

const onToolChange = (value: 'pencil' | 'fill' | 'eraser') => {
  emit('update:tool', value);
};
</script>

<style scoped>
.q-btn {
  margin-right: 8px;
}
</style>
