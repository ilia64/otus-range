#!bin/zsh

cat ip_filter.tsv | ./range > result.tst

diff ip_filter.tst result.tst
