<template>
    <div class="result-block">
        <h2>Reaction Time: {{ this.score }} ms</h2>
        <p class="rank"> {{ rank }} </p>
    </div>
</template>

<script>
export default {
    props: ['score'],
    data() {
        return {
            rank: null
        }
    },
    mounted() {
        if(this.score < 250) {
            this.rank = "First Rank";
        } else if(this.score < 400) {
            this.rank = "Rapid Reflexes"
        } else {
            this.rank = "Snail pace..."
        }
    }
}
</script>

<style>
    .rank {
        font-size: 1.4em;
        color: #0faf87;
        font-weight: bold;
    }
</style>