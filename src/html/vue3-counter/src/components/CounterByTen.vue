<template>
  <div>
      <fieldset>
          <legend><strong>total number is: {{ Counter }}</strong></legend>
          <button @click="increase">Increase</button>
          <button @click="decrease">Decrease</button>
      </fieldset>
  </div>
</template>

<script>
import Vue from 'vue'

export default {
    data() {
        return {
            Counter: 0,
        }
    },
    methods: {
        increase() {
            this.Counter += 10;
        },
        decrease() {
            this.Counter -= 10;
        }
    }
}
</script>

<style>
    legend {
        margin: 0 auto;
    }
    button {
        margin: 10px;
    }
</style>