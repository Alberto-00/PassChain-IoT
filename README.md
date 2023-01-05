<p align="center">
  <img  width="300" src="./Documentazione/Logo_originale.svg">
</p>
<p align="center" dir="auto">
  <img src="./Documentazione/assets/iot.png"/> IoT device for password manager. 
  <img src="./Documentazione/assets/iot.png"/><br>
  A project for IoT Security<br> 
  course at University of Salerno.
</p>

<h1 dir="auto">
  <a id="user-content-project-description-and-introduction" class="anchor" aria-hidden="true" href="#project-description-and-introduction">
    <svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true"><path fill-rule="evenodd" d="M7.775 3.275a.75.75 0 001.06 1.06l1.25-1.25a2 2 0 112.83 2.83l-2.5 2.5a2 2 0 01-2.83 0 .75.75 0 00-1.06 1.06 3.5 3.5 0 004.95 0l2.5-2.5a3.5 3.5 0 00-4.95-4.95l-1.25 1.25zm-4.69 9.64a2 2 0 010-2.83l2.5-2.5a2 2 0 012.83 0 .75.75 0 001.06-1.06 3.5 3.5 0 00-4.95 0l-2.5 2.5a3.5 3.5 0 004.95 4.95l1.25-1.25a.75.75 0 00-1.06-1.06l-1.25 1.25a2 2 0 01-2.83 0z">
      </path>
    </svg>
  </a>
  Project description and introduction
</h1>
<p dir="auto">In this section we introduce context informations for the project.</p>

<h2 dir="auto">
  <a id="user-content-introduction" class="anchor" aria-hidden="true" href="#introduction"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true">
    <path fill-rule="evenodd" d="M7.775 3.275a.75.75 0 001.06 1.06l1.25-1.25a2 2 0 112.83 2.83l-2.5 2.5a2 2 0 01-2.83 0 .75.75 0 00-1.06 1.06 3.5 3.5 0 004.95 0l2.5-2.5a3.5 3.5 0 00-4.95-4.95l-1.25 1.25zm-4.69 9.64a2 2 0 010-2.83l2.5-2.5a2 2 0 012.83 0 .75.75 0 001.06-1.06 3.5 3.5 0 00-4.95 0l-2.5 2.5a3.5 3.5 0 004.95 4.95l1.25-1.25a.75.75 0 00-1.06-1.06l-1.25 1.25a2 2 0 01-2.83 0z">
    </path>
    </svg>
  </a>
  Introduction
</h2>
<p dir="auto">
   <img src="./Documentazione/assets/internet-of-things.png"/> PassChain is an IoT device to store user's credentials (like username and password) and send them to other devices with a Bluetooth connection. Datas are encrypted with AES-128 bit in GCM mode and the board setup is made connecting PassChain to a server Python with a SSL communication. Each operation is authorized only if the user authenticates himself with a fingerprint.
<br>The project is produced for the IoT Security course of Master's Degree in Cybersecurity at University of Salerno.
</p>

<h1 dir="auto">
  <a id="user-content-technical-informations" class="anchor" aria-hidden="true" href="#technical-informations">
    <svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true">
      <path fill-rule="evenodd" d="M7.775 3.275a.75.75 0 001.06 1.06l1.25-1.25a2 2 0 112.83 2.83l-2.5 2.5a2 2 0 01-2.83 0 .75.75 0 00-1.06 1.06 3.5 3.5 0 004.95 0l2.5-2.5a3.5 3.5 0 00-4.95-4.95l-1.25 1.25zm-4.69 9.64a2 2 0 010-2.83l2.5-2.5a2 2 0 012.83 0 .75.75 0 001.06-1.06 3.5 3.5 0 00-4.95 0l-2.5 2.5a3.5 3.5 0 004.95 4.95l1.25-1.25a.75.75 0 00-1.06-1.06l-1.25 1.25a2 2 0 01-2.83 0z">
      </path>
    </svg>
  </a>
  Technical informations
</h1>
<p dir="auto">In this section we introduce technical informations and installing guides!</p>

<h2 dir="auto">
  <a id="user-content-built-with" class="anchor" aria-hidden="true" href="#hardware"><svg class="octicon octicon-link" viewBox="0 0 16 16" version="1.1" width="16" height="16" aria-hidden="true">
    <path fill-rule="evenodd" d="M7.775 3.275a.75.75 0 001.06 1.06l1.25-1.25a2 2 0 112.83 2.83l-2.5 2.5a2 2 0 01-2.83 0 .75.75 0 00-1.06 1.06 3.5 3.5 0 004.95 0l2.5-2.5a3.5 3.5 0 00-4.95-4.95l-1.25 1.25zm-4.69 9.64a2 2 0 010-2.83l2.5-2.5a2 2 0 012.83 0 .75.75 0 001.06-1.06 3.5 3.5 0 00-4.95 0l-2.5 2.5a3.5 3.5 0 004.95 4.95l1.25-1.25a.75.75 0 00-1.06-1.06l-1.25 1.25a2 2 0 01-2.83 0z">
    </path>
    </svg>
  </a>
  Hardware
  </h2>
<p dir="auto">In this section we can see the circuit, in particular, how all the sensors have been connected to the Esp32 and board's datasheet.</p>
<p dir="auto"> <img src="./Documentazione/"/></p>

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
