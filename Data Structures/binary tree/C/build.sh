#!/bin/bash

src="src/*"
out_fd="bin"
out_exe="bt"
out="-c -o ${out_fd}/${out_exe}"

mkdir -p $out_fd

gcc $out $src
