<template>
    <div class="backdrop" @click.self="closeModal">
        <div class="modal" :class="[theme === 'sale' ? 'sale' : (theme === 'dark' ? 'dark' : '')]">
            <slot></slot>
            <div class="actions">
                <slot name="links"></slot>
            </div>
<!--
            <h1> {{ header }} </h1>
            <p> {{ text }} </p>
-->
        </div>
    </div>
</template>

<script>
export default {
    props: ['header', 'text', 'theme'],
    methods: {
        closeModal() {
            this.$emit('close')
        }
    }
}
</script>

<style >
    .modal {
        width: 400px;
        padding: 20px;
        margin: 100px auto;
        background: white;
        border-radius: 10px;
    }
    .backdrop {
        top: 0;
        position: fixed;
        background: rgba(0,0,0,0.5);
        width: 100%;
        height: 100%;
    }
    h1 {
        color: green;
        border: none;
        padding: 0;
    }
    .modal h1 {
        color: green;
        border: none;
        padding: 0;
    }
    .modal p {
        font-style: normal;
        font-weight: bold;
    }
    .modal .actions {
        text-align: center;
        margin: 30px 0 10px 0;
    }
    .modal .actions a {
        color: #333;
        padding: 8px;
        border: 1px solid #eee;
        border-radius: 4px;
        text-decoration: none;
        margin: 10px;
    }
    .modal.sale {
        background: crimson;
        color: white;
    }
    .modal.sale h1 {
        color: white;
    }
    .modal.sale .actions {
        color: white;
    }
    .modal.sale .actoins a {
        color: white;
    }
    .modal.dark {
        background: #686868;
        color: white;
    }
    .modal.dark h1 {
        color: white;
    }
</style>