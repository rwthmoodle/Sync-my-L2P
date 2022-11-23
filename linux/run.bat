docker build -t syncmymoodle -f linux/Dockerfile .
docker run -it --rm -v %cd%:/trans syncmymoodle sh -c "mv /work/linux/Sync*.AppImage /trans/"