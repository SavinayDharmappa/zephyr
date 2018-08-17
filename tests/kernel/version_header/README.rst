.. _version_header:

Version Header
##############

Overview
********
A simple program which add the version header to elf when built
with CONFIG_VERSION_HEADER is enabled:

Building and Running
********************

This project outputs 'KERNEL VERSION' to the console.  It can be built and executed
on QEMU as follows:

.. zephyr-app-commands::
   :zephyr-app: kernel/version_header
   :host-os: unix
   :board: qemu_x86
   :goals: run
   :compact:

Sample Output
=============

.. code-block:: console

    KERNEL VERSION is ${KERNELVERSION}
