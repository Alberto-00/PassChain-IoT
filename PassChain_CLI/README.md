## Generate certificates
Creating a private key
```
openssl genrsa -out domain.key 2048
```
Creating a CSR
```
openssl req -key domain.key -new -out domain.csr
```
Creating a Self-Signed Certificate
```
openssl x509 -signkey domain.key -in domain.csr -req -days 365 -out domain.crt
```
Create a Self-Signed Root CA
```
openssl req -x509 -sha256 -days 1825 -newkey rsa:2048 -keyout rootCA.key -out rootCA.crt
```
Create a configuration text file domain.ext
```
authorityKeyIdentifier=keyid,issuer
basicConstraints=CA:FALSE
subjectAltName = @alt_names
[alt_names]
DNS.1 = example.org
```
Sign domain.csr
```
openssl x509 -req -CA rootCA.crt -CAkey rootCA.key -in domain.csr -out domain.crt -days 365 -CAcreateserial -extfile domain.ext
```
.crt to .pem
```
openssl x509 -in mycert.crt -out mycert.pem -outform PEM
```
Notes: CN and DNS.1 is the hostname that must be set in the client

Link: [Creating a Self-Signed Certificate With OpenSSL](https://www.baeldung.com/openssl-self-signed-cert)

<h2 dir="auto">
  <a id="user-content-authors" class="anchor" aria-hidden="true" href="#authors">
    <svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M7.775 3.275a.75.75 0 001.06 1.06l1.25-1.25a2 2 0 112.83 2.83l-2.5 2.5a2 2 0 01-2.83 0 .75.75 0 00-1.06 1.06 3.5 3.5 0 004.95 0l2.5-2.5a3.5 3.5 0 00-4.95-4.95l-1.25 1.25zm-4.69 9.64a2 2 0 010-2.83l2.5-2.5a2 2 0 012.83 0 .75.75 0 001.06-1.06 3.5 3.5 0 00-4.95 0l-2.5 2.5a3.5 3.5 0 004.95 4.95l1.25-1.25a.75.75 0 00-1.06-1.06l-1.25 1.25a2 2 0 01-2.83 0z">
      </path>
    </svg>
  </a>
  Authors
</h2>
<ul dir="auto">
<li><strong>Alberto Montefusco</strong>   - <em>Developer</em>   - <a href="https://github.com/Alberto-00">Alberto-00</a></li>
</ul>
