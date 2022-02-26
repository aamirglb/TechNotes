var Roles;
(function (Roles) {
    Roles[Roles["ADMIN"] = 0] = "ADMIN";
    Roles[Roles["READ_ONLY"] = 1] = "READ_ONLY";
    Roles[Roles["AUTHOR"] = 2] = "AUTHOR";
})(Roles || (Roles = {}));
;
// Concrete object
var person = {
    // const person = {
    name: "Aamir Ali",
    age: 30,
    hobbies: ["cooking", "playing"],
    roles: [2, Roles.ADMIN]
};
console.log(person);
// console.log(person.nickname)
for (var _i = 0, _a = person.hobbies; _i < _a.length; _i++) {
    var hobby = _a[_i];
    console.log(hobby.toUpperCase());
}
