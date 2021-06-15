These files are needed for building with qt5.15 on Ubuntu 18.04. Since they are not there on GitHub Actions buildservers, we built them manually and checked them in.

## Build
Here's how to build these libraries:
```bash
sudo apt install gcc g++ build-essential
mkdir /tmp/icu
cd /tmp/icu
wget https://github.com/unicode-org/icu/releases/download/release-56-2/icu4c-56_2-src.tgz
tar xzf ./icu4c-56_2-src.tgz
cd icu/source
./configure
make
```