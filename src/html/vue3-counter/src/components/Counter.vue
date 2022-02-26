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
            this.Counter += 1;
        },
        decrease() {
            this.Counter -= 1;
        }
    }
}
</script>

<style>
    fieldset {
        margin: 0px 350px ;
        width: 50%
    }
    legend {
        margin: 0 auto;
    }
    button {
        margin: 10px;
    }
</style>