*La instalación de xv6 fue realizada en un sistema operativo Linux Mint*

<h1>Pasos seguidos para la instalación de xv6</h1>
<h2>Instalacion RISC-V GNU Compiler Toolchain</h2>
<ol>
    <li>Se instala RISC-V GNU Compiler Toolchain y sus dependencias correspondientes. Para esto se clona el repositorio oficial: <pre><code>$ git clone https://github.com/riscv/riscv-gnu-toolchain</code></pre> </li>
    <li>Luego se instalan los prerequisitos correspondientes a Ubuntu (Mint y Ubuntu son variantes de Debian). <pre><code>$ sudo apt-get install autoconf automake autotools-dev curl python3 python3-pip libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev ninja-build git cmake libglib2.0-dev libslirp-dev</code></pre> </li>
<li>Se ingresa a la carpeta riscv-gnu-toolchain creada por git clone, y se ejecuta el script de configuración y make para armar el compilador (se utiliza newlib ya que es la version más simple y por ende mas ligera de armar, esto será suficiente para los requerimientos de xv6). 
    <br><pre><code>./configure --prefix=/opt/riscv</code>
    <br> <code>make newlib</code></pre>
</li>
<li>Una vez terminada la construcción del compilador RISCV se agrega este a nuestro PATH. 
    <br><pre><code>export PATH=/opt/riscv/bin:$PATH</code></pre>
</li>
<li></li>
</ol>

<h2>Instalación simulador QEMU</h2>
<ol>
    <li> Se instalan paquetes requeridos y recomendados por https://wiki.qemu.org/Hosts/Linux (Documentación oficial)
        <pre><code>sudo apt-get install git-email
sudo apt-get install git libglib2.0-dev libfdt-dev libpixman-1-dev zlib1g-dev ninja-build
sudo apt-get install libaio-dev libbluetooth-dev libcapstone-dev libbrlapi-dev libbz2-dev
sudo apt-get install libcap-ng-dev libcurl4-gnutls-dev libgtk-3-dev
sudo apt-get install libibverbs-dev libjpeg8-dev libncurses5-dev libnuma-dev
sudo apt-get install librbd-dev librdmacm-dev
sudo apt-get install libsasl2-dev libsdl2-dev libseccomp-dev libsnappy-dev libssh-dev
sudo apt-get install libvde-dev libvdeplug-dev libvte-2.91-dev libxen-dev liblzo2-dev
sudo apt-get install valgrind xfslibs-dev </code></pre>
    </li>
    <li>Se clona el repositorio oficial de QEMU en nuestro PC, e ingresamos a la carpeta.
    <br><pre><code>git clone https://gitlab.com/qemu-project/qemu.git
cd qemu</code></pre>
    </li>
    <li>Se configura QEMU para la arquitectura indicada por la documentación de xv6, riscv64-softmmu
    <br><pre><code>./configure --target-list=riscv64-softmmu --prefix=/opt/qemu
</code></pre>
    </li>
    <li>Se procede a construir e instalar QEMU. Además si instala tomli ya que sino tira un error.
    <br><pre><code>pip3 install tomli
make -j$(nproc)
sudo make install</code></pre>
    *j$(nproc) utiliza todos los nucles disponibles de la CPU, acelerando así el proceso.*
    </li>
    <li>Agregamos QEMU a nuestro PATH
    <br><pre><code>export PATH=/opt/qemu/bin:$PATH
</code></pre>
    </li>
</ol>
<h2>Compilar y ejecutar XV6</h2>
<ul>
    <li>Se realiza un fork del repositorio de xv6: https://github.com/mit-pdos/xv6-riscv . Luego se clona este en nuestro PC y se ingresa a la carpeta xv6-riscv.
    <br><pre><code>git clone https://github.com/benjamin-contreas/xv6-riscv.git
cd xv6-riscv</code></pre>
    </li>
    <li>Ejecutamos el comando <code>make qemu</code> con esto ya estamos dentro de una terminal xv6 en QEMU.</li>
    <li>Ejecutamos los comandos de prueba:
    <br><pre><code>$ ls
$ echo "Hola xv6"
$ cat README</code></pre>
    </li>
</ul>
