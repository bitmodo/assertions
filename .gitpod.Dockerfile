FROM gitpod/workspace-full:build-branch-master

USER root

# Install system packages
RUN apt-get update \
    && apt-get install -yq --no-install-recommends \
        python3=3.7.3-1 \
        python3-pip=18.1-5 \
        python3-setuptools=40.8.0-1 \
        python3-wheel=0.32.3-2 \
        valgrind=1:3.14.0-2ubuntu6 \
        ccache=3.6-1 \
    && /usr/sbin/update-ccache-symlinks \
    && apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/*

# Install libvirt packages
RUN apt-get update \
    && apt-get install -yq --no-install-recommends \
        ruby-libvirt=0.7.1-1 \
    && apt-get install -yq --no-install-recommends \
        qemu=1:3.1+dfsg-2ubuntu3.7 \
        qemu-kvm=1:3.1+dfsg-2ubuntu3.7 \
        libvirt-daemon-system=5.0.0-1ubuntu2.6 \
        libvirt-clients=5.0.0-1ubuntu2.6 \
        ebtables=2.0.10.4+snapshot20181205-1ubuntu1 \
        dnsmasq-base=2.80-1ubuntu1 \
    && apt-get install -yq --no-install-recommends \
        libxml2-dev=2.9.4+dfsg1-7ubuntu3 \
        libvirt-dev=5.0.0-1ubuntu2.6 \
        zlib1g-dev=1:1.2.11.dfsg-1ubuntu2 \
        ruby-dev=1:2.5.1 \
    && apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/*

# Download and install Vagrant
RUN curl -O https://releases.hashicorp.com/vagrant/2.2.7/vagrant_2.2.7_x86_64.deb \
    && apt install ./vagrant_2.2.7_x86_64.deb \
    && usermod -a -G libvirt gitpod \
    && apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/*

USER gitpod

# Install packages
RUN python3 -m pip install pip==20.0.2 meson==0.53.0 gcovr==4.2 ninja==1.9.0.post1 \
    && brew install git-flow \
#    && bundle install \
    && vagrant plugin install vagrant-libvirt
