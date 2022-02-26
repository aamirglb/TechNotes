<template>
  <Counter />
  <br /> <br />
  <CounterByTen />
</template>

<script>
import Counter from './components/Counter.vue';
import CounterByTen from './components/CounterByTen.vue'

export default {
  name: 'App',
  components: {
    Counter,
    CounterByTen
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
