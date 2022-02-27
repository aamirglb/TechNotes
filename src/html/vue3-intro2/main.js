const app = Vue.createApp({
    data: function() {
        return {
            cart: 0,
            product: 'Socks',
            //description: "Buy different types of socks"
            image: "./assets/images/socks_green.jpg",
            //inventory: 0
            inStock: true,
            details: ['50% cotton', '30% wool', '20% polyester'],
            variants: [
                {id: 2234, color: 'green', image: './assets/images/socks_green.jpg'},
                {id: 2235, color: 'blue', image: './assets/images/socks_blue.jpg'},
            ]
        }
    },
    methods: {
        addToCart() {
            this.cart += 1
        },
        clearCart() {
            this.cart = 0
        },
        updateImage(variantImage) {
            this.image = variantImage
        }
    }
})
