enum Roles {
    ADMIN, READ_ONLY, AUTHOR,
};

// Concrete object
const person: {
    name: string;
    age: number;
    hobbies: string[];
    roles: [number, Roles];

} = {
// const person = {
    name: "Aamir Ali",
    age: 30,
    hobbies: ["cooking", "playing"],
    roles: [2, Roles.ADMIN]
};

console.log(person)
// console.log(person.nickname)

for(const hobby of person.hobbies) {
    console.log(hobby.toUpperCase())
}