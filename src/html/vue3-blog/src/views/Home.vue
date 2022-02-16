<template>
  <div class="home">
    <p ref="p">My name is "{{ person.name }}" and I'm {{ person.age }} years old. </p>
    <button @click="handleClick">Click Me</button>
    <button @click="age++">Increase Age</button>
    <button @click="updatePerson">Update person</button>
    <button @click="updatePerson2">Update person-2</button>
    <input type="text" v-model="name">

    <h2>Reactive</h2>
    <p>{{ person2.name }} - {{person2.age}}</p>
  </div>
</template>

<script>
import { reactive, ref } from 'vue'
// @ is an alias to /src

export default {
  name: 'Home',
  setup() {
    const person = ref({name: 'aamir', age: 30})
    const person2 = reactive({name: 'ali', age: 35})

    const updatePerson = () => {
      person.value.age = 40
    }

    const updatePerson2 = () => {
      person2.age = 45
    }
    console.log('setup')

    const p = ref(null)

    const name = ref('aamir')
    const age = ref(30)

    const handleClick = () => {
      name.value = 'mohammad'
      age.value = 35
      // console.log(p, p.value)
      // p.value.classList.add('test')
      // p.value.textContent = "Hello World!!"

    }
    return {
      // name, age, handleClick, p
      person, updatePerson, person2, updatePerson2
    }
  },
}
</script>
