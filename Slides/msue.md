<h1 class="title">Manual Systemd Unit Execution</h1>
<h2 class="subtitle">Anàlisi, execució y creació de les Systemd Unit</h2>
<p class="author">Bruno Mondelo &mdash; 2017-05-23</p>

---

<h2 class="section-title">Index</h2>
<ul class="index-list">
  <li class="index-purple">Què es una <strong>Unit</strong>?</li>
  <li class="index-purple">Quines <strong>Unit</strong> hi ha?</li>
  <li class="index-purple">Es poden crear noves Unit? <strong>Com</strong>?</li>
  <li class="index-purple">Realització <strong>manual</strong> de les Unit</li>
  <li class="index-purple">Conclusió</li>
</ul>

---

<h2 class="section-title">Què es una Unit?</h2>
<ul class="index-list">
  <li class="index-blue">Contingut</li>
  <li class="index-blue">On estan?</li>
</ul>

---

<h2 class="section-title">Quines Unit hi ha?</h2>
<ul class="index-list">
  <li class="index-orange">Mount</li>
  <li class="index-orange">Automount</li>
  <li class="index-orange">Swap</li>
  <li class="index-orange">Device</li>
  <li class="index-orange">Service</li>
  <li class="index-orange">Socket</li>
  <li class="index-orange">Path</li>
  <li class="index-orange">Timer</li>
  <li class="index-orange">Scope</li>
  <li class="index-orange">Slice</li>
  <li class="index-orange">Snapshot</li>
  <li class="index-orange">Target</li>
</ul>

---

<h3 class="section-title">Mount</h3>
<ul class="index-list">
  <li class="index-green">Informació de un <strong>mount point</strong></li>
  <li class="index-green"><strong>FSTAB</strong> Vs. Systemd Mount</li>
  <li class="index-green">Nom especific</li>
</ul>

---

<h3 class="section-title">Automount</h3>
<ul class="index-list">
  <li class="index-green">Munta automàticament un <strong>mount point</strong></li>
  <li class="index-green"><strong>Requereix</strong> de una Unit Mount</li>
  <li class="index-green">Nom especific</li>
</ul>

---

<h3 class="section-title">Swap</h3>
<ul class="index-list">
  <li class="index-green">Dispositius <strong>Swap</strong></li>
  <li class="index-green"><strong>Paginació</strong> controlada per Systemd</li>
  <li class="index-green"><strong>FSTAB</strong> Vs. Systemd Swap</li>
  <li class="index-green">Nom especific</li>
</ul>

---

<h3 class="section-title">Device</h3>
<ul class="index-list">
  <li class="index-green">Dispositius marcat per <strong>udev</strong></li>
</ul>

---

<h3 class="section-title">Service</h3>
<ul class="index-list">
  <li class="index-gold">Processos</li>
</ul>

---

<h3 class="section-title">Socket</h3>
<ul class="index-list">
  <li class="index-gold">Activació de un <strong>Service</strong> basat en socket</li>
  <li class="index-gold">IPC (Inter-Process Comunication)</li>
  <li class="index-gold">Network Sockets</li>
  <li class="index-gold">FIFO</li>
</ul>

---

<h3 class="section-title">Path</h3>
<ul class="index-list">
  <li class="index-gold">Activació de una <strong>Unit</strong> basat en un path</li>
  <li class="index-gold">Nom especific</li>
</ul>

---

<h3 class="section-title">Timer</h3>
<ul class="index-list">
  <li class="index-gold">Activació de una <strong>Unit</strong> basat en un temps</li>
  <li class="index-gold">Nom especific</li>
</ul>

---

<h3 class="section-title">Scope</h3>
<ul class="index-list">
  <li class="index-red">Configura un grup de processos</li>
  <li class="index-red">Controla els <strong>recursos</strong></li>
  <li class="index-red">No es configuren. <strong>Dinàmicament</strong> es creen</li>
</ul>

---

<h3 class="section-title">Slice</h3>
<ul class="index-list">
  <li class="index-red">Controla de manera <strong>jeràrquica</strong> un grup de processos</li>
  <li class="index-red">Permet configurar els recursos</li>
</ul>

---

<h3 class="section-title">Snapshot</h3>
<ul class="index-list">
  <li class="index-turqoise">Guarda el <strong>status</strong> de Systemd</li>
  <li class="index-turqoise">Son volàtils</li>
  <li class="index-turqoise">Permeten fer <strong>rollback</strong></li>
</ul>

---

<h3 class="section-title">Target</h3>
<ul class="index-list">
  <li class="index-turqoise">Grup de <strong>Unit</strong></li>
  <li class="index-turqoise">Permeten canviar de Unit</li>
  <li class="index-turqoise"><strong>SysVinit</strong> traducció</li>
</ul>

---

<h2 class="section-title">Realització manual de les Unit</h2>
<ul class="index-list">
  <li class="index-fuchsia">Timer</li>
  <li class="index-fuchsia">Path</li>
  <li class="index-fuchsia">Socket</li>
</ul>

---

<h3 class="section-title">Timer</h3>
<ul class="index-list">
  <li class="index-gold">Crond</li>
</ul>

---

<h3 class="section-title">Path</h3>
<img class="flow-image" src="path-flow.png" />

---

<h3 class="section-title">Socket</h3>
<img class="flow-image" src="socket-flow.png" />

---

<h2 class="section-title">Conclusió</h2>

---

<img class="bye-bye" src="end.png" />
