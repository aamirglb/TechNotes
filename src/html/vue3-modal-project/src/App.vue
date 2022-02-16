<template>
  <h1> {{ title }} </h1>
<!--
  <input type="text" ref="name">
  <button @click="handleClick">click me</button>
-->
  <div v-if="showModal">
<!--    <Modal :header="header" :text="text" theme="" @close="toggleModal" /> -->
    <Modal theme="sale" @close="toggleModal">
      <template v-slot:links>
        <a href="#">sign up now</a>
        <a href="#">more info</a>
      </template>
      <h1>Sale</h1>
      <p>Special Offer 50% off</p>
    </Modal>
  </div>
  <br>
  <button @click.alt="toggleModal">Open Modal (alt)</button>
</template>

<script>
import Modal from './components/Modal.vue'

export default {
  name: 'App',
  components: {
    Modal
  },
  data() {
    return {
      title: 'My First Vue App :)',
      header: "Sign Up For The Giveaway!",
      text: "Grab the course for half price!",
      showModal: false
    }
  },
  methods: {
    handleClick() {
      console.log(this.$refs.name)
      this.$refs.name.classList.add('active')
      this.$refs.name.focus()
    },
    toggleModal() {
      this.showModal = !this.showModal
    }
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
h1 {
  border-bottom: 3px solid #ddd;
  display: inline-block;
  padding-bottom: 10px;
}
</style>
