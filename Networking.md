# Computer Networks

* TCP/IP is a protocol suite that implements the Internet architecture and draws its origins from the ARPANET Reference Model (ARM) [RFC0871].

![](images/net/msg_boundary_concept.png)

* When an application sends more than one chunk of information into the network, the fact that more than one chunk was written may or may not be preserved by the communication protocol.

* Most datagram protocols preserve message boundaries.

| Services | Ports |
|----------|-------|
| Secure Shell Protocol (SSH) | 22 |
| File Transfer Protocol (FTP) | 20 and 21|
| Telnet remote terminal protocol | 23 |
| e-mail/Simple Mail Transfer Protocol (SMTP) | 25 | 
| Domain Name System (DNS) | 53 | 
| Hypertext Transfer Protocol or Web (HTTP and HTTPS) | 80 and 443 | 
| Interactive Mail Access Protocol (IMAP and IMAPS | 143 and 993 |
| Simple Network Management Protocol (SNMP) |  161 and 162 | 
| Lightweight Directory Access Protocol (LDAP) | 389 |

* In the TCP/IP world, the **DNS** is a distributed database that provides the mapping between host names and IP addresses (and vice versa).

* Every official standard in the Internet community is published as a _Request for Comments_, or **RFC**. [RFC](http://www.rfc-editor.org.)

* The historical de facto standard TCP/IP implementations were from the _Computer Systems Research Group (CSRG)_ at the University of California, Berkeley. They were distributed with the 4.x BSD (Berkeley Software Distribution) system and with the BSD Networking Releases until the mid-1990s.

* malicious users are able to insert whatever IP address they choose into the source IP address field of each IP datagram they send, an activity called _spoofing_.

* _Denial-of-service (DoS)_ attacks usually involve using so much of some important resource that legitimate users are denied service. This is often accomplished by using many sending computers, forming a _distributed DoS (DDoS)_ attack.

* The dotted-quad notation is simply a way of writing the whole IPv4 address; a 32-bit nonnegative integer used throughout the Internet system; using convenient decimal numbers.

* In IPv6, addresses are 128 bits in length, four times larger than IPv4 addresses.