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

Page 34