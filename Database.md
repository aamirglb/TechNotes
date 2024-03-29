# SQLite

* SQLite is a zero-configuration, standalone, relational database engine that is designed to be embedded directly into an application.

* A Relational Database Management System (RDBMS) are used to store user-defined records in large tables

* Popular RDBMS
    * Oracle Database
    * IBM's DB2
    * Microsoft's SQL Server
    * MySQL (open source)
    * PostgreSQL (open source)

* SQLite is
    * Serverless
    * Zero Configuration
    * Cross-Platform
    * Self-Contained
    * Small Runtime Footprint
    * Transactional (ACID-compliant, allowing safe access from multiple processes or threads)
    * Full-Featured (full featured query language SQL92/SQL2 standard)
    * Highly Reliable

* That single file contains the database layout as well as the actual data held in all the different tables and indexes.

* Using the default configuration, the compiled SQLite library is less than 700 KB on most platforms, and requires less than 4 MB of memory to operate. By omitting the more advanced features, the library can often be trimmed to 300 KB or less. With minor configuration changes, the library can be made to function on less than 256 KB of memory.

* all file and storage access is done through a _Virtual File System (VFS)_ interface.

* SQLite uses a **dynamic-type system** for tables. The SQLite engine will allow you to put any value into nearly any column, regardless of type.

* SQLite allows a single database connection to associate itself with multiple database files simultaneously. This allows SQLite to process SQL statements that bridge across multiple databases.

* SQLite is capable of creating databases that are held entirely in memory.

* Unlike many RDBMS products, the SQLite library is able to access read-only database files. This allows data stores to be read directly from an optical disc or other read-only filesystem.

* The concurrency protection offered by SQLite depends on file locks to protect
against data loss.

* An SQLite database has no authentication or authorization data. Instead, SQLite depends on filesystem permissions to control access to the raw database file.

* The official code distribution is known as the amalgamation. The amalgamation is a single C source file that contains the entire SQLite core.

```shell
# open (or create) a database
$ sqlite3 test.db
```

* In addition to processing SQL statements, there is a series of shell-specific commands.
These are sometimes referred to as “dot-commands” because they start with a period.

* The `.read` command can be used to execute a file full of SQL commands. Dot-commnands must be given on one line, and should not end in a semicolon.

* `.headers` and `.mode` control some aspect of the database output. Turning headers on and setting the output mode to column will produce a table that most people find easier to read.

```shell
sqlite> .headers on
sqlite> .mode column
```

* `.schema` command will list all of the DDL commands (CREATE TABLE, CREATE INDEX, etc.) used to define the database.

* **Structured Query Language**, or SQL. pronounced “sequel,” the official pronunciation is to name each letter as “ess-cue-ell.”

* The SQL language is the main means of interacting with nearly all modern
relational database systems.

* The core of SQL is a _declarative language_. In a declarative language, you state what you want the results to be and allow the language processor to figure out how to deliver the desired results. Compare this to _imperative languages_, such as C, Java, Perl, or Python, where each step of a calculation or operation must be explicitly written out, leaving it up to the programmer to lead the program, step by step, to the correct conclusion.

* Most SQL commands take the form verb-subject. For example, CREATE (verb)
TABLE (subject), DROP INDEX , UPDATE table_name.

* SQL’s biggest flaw is that formal standardization has almost always followed common implementations. Almost every database product (including SQLite) has custom extensions and enhancements to the core language that help differentiate it from other products, or expose features or control systems that are not covered by the core SQL standard.

* SQL is a case-insensitive language. All commands and keywords are case insensitive, as are identifiers (such as table names and column names).

* SQL is whitespace insensitive, including line breaks. Individual statements are separated by a semicolon.

* Single-line comments start with a double dash ( -- ) and go to the end of the line. SQL also supports multi-line comments using the C comment syntax (/* */).

* Text literals are enclosed in single quotes (' '). To represent a string literal that includes a single quote character, use two single quotes in a row ( publisher = 'O''Reilly' ). C-style backslash escapes ( \' ) are not part of the SQL standard and are not supported by SQLite.

* SQL allows any value to be assigned a NULL. NULL is not a value in itself (SQLite actually implements it as a unique valueless type), but is used as a marker or flag to represent unknown or missing data.

* **Three-valued logic** is often abbreviated TVL or 3VL, and is more formally known as ternary logic. 3VL essentially adds an “unknown” state to the familiar true/false Boolean logic system.

* You cannot use the equality operator ( = ) to test for NULLs. You must
use the `IS NULL` operator.

* `IN` `LIKE` `GLOB` `MATCH` `REGEXP`. These five keywords are logic operators, returning, true, false, or NULL state.

* SQL commands are divided into four major categories
    * Data Definition Language (DDL) : define the structure of tables, views, indexes, and other data containers and objects. `CREATE TABLE`, `DROP VIEW`
    * Data Manipulation Language (DML): insert, update, delete and query actual data values. `INSERT`, `SELECT`.
    * Transaction Control Language (TCL): control transactions. `BEGIN`, `COMMIT`
    * Data Control Language (DCL): grant or revoke access control. `GRANT`, `REVOKE`. SQLite lacks DCL commands.

* DDL commands define the basic structure of the database and are typ-
ically run when a new database is created.

```shell
    CREATE TABLE table_name
    (
        column_name column_type,
        [...]
    );
```

* Most databases use strong, static column typing. This means that the elements of a column can only hold values compatible with the column’s defined type. SQLite utilizes a dynamic typing technique known as _manifest typing_.

* In the stric sense, SQLite supports only **five** concrete datatypes. These are known as _storage classes_, and represent the different ways SQLite might choose to store data on disk.

    * **NULL**
    * **Integer**: 1, 2, 3, 4, 6 or 8 bytes in length
    * **Float**: 8-byte value in processor's native format (IEEE 754 double precision number)
    * **Text**: A variable-length string, stored using database encoding (UTF-8, UTF-16BE, or UTF-16LE)
    * **BLOB**: (Binary Large Object) raw bytes, represented as hexadecimal text strings preceded by an `x`. Ex: `x'1234ABCD'`

* Rather than being an absolute type, as in most databases, an SQLite column type (as defined in CREATE TABLE ) becomes more of a suggestion than a hard and fast rule. This is known as a _type affinity_, and essentially represents
a desired category of type.

* Each table column must have one of five type affinities:
    * Text: `CHAR`, `CLOB` `TEXT`
    * Numeric: If no match
    * Integer: `INT`
    * Float: `REAL`, `FLOA` `DOUB`
    * None: `BLOB`

```
CREATE TABLE table_name
(
    column_name column_type  column_constraints...,
    [... ,]

    table_constraints,
    [...]
);
```

* To help with date and time defaults, SQLite also includes three special keywords that may be used as a default value: `CURRENT_TIME` , `CURRENT_DATE` , and `CURRENT_TIMESTAMP`.

```
CREATE TABLE parts
(
part_id INTEGER PRIMARY KEY,
stock   INTEGER DEFAULT 0 NOT NULL,
desc    TEXT CHECK( desc != '' )  -- empty strings not allowed
);
```

* There is some expense in maintaining an index, so be aware that enforcing a UNIQUE column constraint can have performance considerations.

* a single column (or set of columns) can be des-
ignated as the PRIMARY KEY . Each table can have only one primary key.

* In SQLite, `PRIMARY KEY` does not imply `NOT NULL`. This is in contradiction to the SQL standard and is considered a bug,

* In addition to a `PRIMARY KEY`, columns can also be marked as a `FOREIGN KEY`. These columns reference rows in another (foreign) table. Foreign keys can be used to create links between rows in different tables.

* Compound primary key

```
CREATE TABLE rooms
(
    room_number      INTEGER NOT NULL,
    building_number  INTEGER NOT NULL,
    [...,]

    PRIMARY KEY( room_number, building_number )
);
```

* Create a table from the output of a query.

```
CREATE [TEMP] TABLE table_name AS SELECT query_statement;
```

* SQLite supports a limited version of the ALTER TABLE command. Currently, there are only two operations supported by ALTER TABLE : `add column` and `rename`.

* `DROP TABLE` command is used to delete a table.

```
DROP TABLE table_name;
```

* Virtual tables can be used to connect any data source to SQLite, including other databases. A virtual table is created with the `CREATE VIRTUAL TABLE` command.

* Views provide a way to package queries into a predefined object. Once created, views act more or less like read-only tables.

```
CREATE [TEMP] VIEW view_name AS SELECT query_statement
```

* A view is fully dynamic. Every time the view is referenced or queried,
the underlying SELECT statement is run to regenerate the view.

* Indexes (or indices) are a means to optimize database lookups by pre-sorting and indexing one or more columns of a table.

```
CREATE [UNIQUE] INDEX index_name ON table_name ( column_name [, ...] );
```

* There are three commands used for adding, modifying, and removing data from the database. `INSERT` adds new rows, `UPDATE` modifies existing rows, and `DELETE` removes rows.

```
INSERT INTO table_name (column_name [, ...]) VALUES (new_value [, ...]);
```

* To speed up bulk inserts, it is common to wrap groups of 1,000 to 10,000 `INSERT` statements into a single transaction. Grouping the statement together will substantially increase the overall speed of the inserts by delaying the physical I/O until the end of the transaction.

```
INSERT INTO table_name (column_name, [...]) SELECT query_statement;
```

* The `UPDATE` command is used to assign new values to one or more columns of existing rows in a table.

```
UPDATE table_name SET column_name=new_value [, ...] WHERE expression
```

* The `DELETE` command is used to delete or remove one or more rows
from a single table.

```
DELETE FROM table_name WHERE expression;
```

```
SELECT output_list FROM input_table WHERE row_filter;

sqlite> CREATE TABLE tbl (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, a, b, c);
sqlite> INSERT INTO tbl (a, b, c) VALUES (10,10,10);
sqlite> INSERT INTO tbl (a, b, c) VALUES (20,30,35);
sqlite> INSERT INTO tbl (a, b, c) VALUES (15,19,12);
sqlite> SELECT a FROM tbl WHERE id=1 OR id=2 OR id=3;
```

* A _transaction_ is used to group together a series of low-level changes into a single, logical update.

* The standard for reliable, robust transactions is the **ACID** test. ACID stands for _Atomic_, _Consistent_, _Isolated_, and _Durable_.

* SQLite is in autocommit mode. This means that SQLite will automatically
start a transaction for each command, process the command, and (assuming no errors were generated) automatically commit the transaction.

* The `BEGIN` command is used to start or open a transaction. Once an explicit transaction has been opened, it will remain open until it is committed or rolled back. The keyword TRANSACTION is optional:

```
BEGIN [ DEFERRED | IMMEDIATE | EXCLUSIVE ] [TRANSACTION]
```

# MongoDB

* Mongo DB stores its information in documents rather than rows.

```
{
_id: 10,
username: 'peter',
email: 'pbbakkum@gmail.com'
}
```

* Mongo DB features

    * secondary indexes,
    * range queries,
    * sorting,
    * aggregations, and
    * geospatial indexes

* A **document-based data model** can represent rich, hierarchical data structures. It’s often possible to do without the multitable joins common to relational databases.

* MongoDB’s data model is document-oriented.

* A JSON document needs double quotes everywhere except for numeric values. While for JavaScript version of a JSON document double quotes aren’t necessary.

* A _document_ is essentially a set of property names and their values. The values can be simple data types, such as strings, numbers, and dates. But these values can also be arrays and even other JSON documents.

* Internally, MongoDB stores documents in a format called **Binary JSON**, or **BSON**.

* The MongoDB shell uses JavaScript and gets documents in JSON,

* Where relational databases have _tables_, MongoDB has _collections_. In other words, MySQL keeps its data in tables of rows, while Mongo DB keeps its data in collections of documents, which you can think of as a group of documents.

* In theory, each document in a collection can have a completely different structure; in practice, a collection’s document will be relatively uniform.

* Indexes in MongoDB are implemented as a B-tree data structure. B-tree indexes,
also used in many relational databases, are optimized for a variety of queries, includ-
ing range scans and queries with sort clauses.

* create, read, update, and delete (CRUD)

* databases in MongoDB are just namespaces to distinguish between collections.

* All collections in a database are grouped in the
same files, so it makes sense, from a memory perspective, to keep related collections
in the same database.

* A query selector is a
document that’s used to match against all documents in the collection.

* MongoDB’s `$and` operator

* MongoDB uses opportunistic locking in its **WiredTiger storage engine** to maximize concurrency and throughput.

* Every document has a special key, "_id", that is unique within a collection.

* By default MongoDB listens for socket connections on port `27017`

* On startup, the shell connects to the `test` database on a MongoDB server and assigns this database connection to the global variable `db`.

* The `insertOne` function adds a document to a collection.

* find and findOne can be used to query a collection.

* If we would like to modify our post, we can use `updateOne`.

* Basic Data Types

    * Null
        `{"x" : null }`

    * Boolean
        `{"x": true}`

    * Number
        ```
            {"x": 3.14}
            {"x": 3 }
            {"x": NumberInt("3")}
            {"x": NumberLong("3")}
        ```
    * String
        `{"x": "foobar"}
    * Date: 64-bit integers representing milliseconds since the Unix
epoch (January 1, 1970)
            `{"x": new Date()}

    * Regular Expression
    * Array
    * Embedded document
    * Object ID
    * Binary data
    * Code

* The "_id" key’s value can be any type, but it defaults to an `ObjectId`.

* ObjectIds use 12 bytes of storage, which gives them a string representation that is 24
hexadecimal digits

* `Mongoose` is a Object Data Modeling (ODM) library for MongoDB distributed as an npm package. Mongoose is a Node.js-based Object Data Modeling (ODM) library for MongoDB. The problem that Mongoose aims to solve is allowing developers to enforce a specific schema at the application layer.

### mongodb getting started

* Install `mongosh` to connect to mongodb server

```bash
# connect to server
mongosh.exe "mongodb://localhost:27017"

# show all databases
show databases
show dbs

# show all collections
db.getCollectionNames()

# list content of a collection
db.<collection-name>.find()

# find number of documents in a collection
db.<collectoin-name>.count()

# delete all documents from the collection
db.<collection-name>.deleteMany({})
```
