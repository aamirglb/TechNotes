console.log('hello, vue')

const app = Vue.createApp({
    // setup any data or function
    // component template
    // template: '<h2>I am the template</h2>'

    data() {
        return {
            url: "http://www.thenetninja.co.uk",
            title: "The Final Empire",
            author: "Brandon Sanderson",
            age: 45,
            count: 0,
            showBooks: true,
            x: 0,
            y: 0,
            books: [
                { title: "Professional C++", author: "Marc Gregoire", img: "assets/1.png", isFav: true},
                { title: "The C++ Standard Library", author: "Nicolai M. Josuttis", img: "assets/2.png", isFav: false },
                { title: "C++ Programming Language", author: "Bjarne Stroustrup", img: "assets/3.png", isFav: true}
            ]
        }
    },
    methods: {
        changeTitle(title) {
            this.title = `${title} - ${++this.count}`;
            console.log("You clicked me")
        },
        toggleShowBooks() {
            this.showBooks = !this.showBooks
        },
        handleEvent(e, data) {
            console.log(e.type)
            if(data) {
                console.log(data)
            }
        },
        handleMouseMove(e) {
            this.y = e.offsetY
            this.x = e.offsetX
        },
        toggleFav(e, book) {
            book.isFav = !book.isFav
            //if(title == "Professional C++") {
            //    this.books[0].isFav = !this.books[0].isFav
            //} else if(title == "The C++ Standard Library") {
            //    this.books[1].isFav = !this.books[1].isFav
            //} else {
            //    this.books[2].isFav = !this.books[2].isFav
            //}
        }
    },
    computed: {
        filteredBooks() {
            return this.books.filter(book => book.isFav)
        }
    }
})

app.mount('#app')