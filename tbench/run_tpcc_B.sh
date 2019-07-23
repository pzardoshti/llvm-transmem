#!/bin/bash

if [ -f tpccbp_f1.txt ] ; then
    rm tpccbp_f1.txt
fi

if [ -f tpccbp_f2.txt ] ; then
    rm tpccbp_f2.txt
fi

#Number of threads
THREADS="1 2 4 8 16 24 32 48"
# Define STM and PTM variables with a value
TMLIB="cgl_mutex orec_eager_quiescence orec_lazy_quiescence orec_mixed_quiescence norec_quiescence ring_sw tlrw_eager \
pn_cgl_eager pn_orec_eager pn_orec_lazy pn_orec_mixed pn_norec pn_ring_sw pn_tlrw_eager pn_cgl_lazy"

PTMLIB="pg_cgl_eager pg_orec_eager pg_orec_lazy pg_orec_mixed pg_norec pg_ring_sw pg_tlrw_eager pg_cgl_lazy \
pi_cgl_eager pi_orec_eager pi_orec_lazy pi_orec_mixed pi_norec pi_ring_sw pi_tlrw_eager pi_cgl_lazy"

for i in $THREADS
do
    for t in $TMLIB
    do
        echo "Running TPCC (Bplustree) with $t and $i threads ..."
        numactl -N 0 ./obj64/tpcc_B+_$t -d 5 -t $i >> tpccbp_f1.txt
        echo -n "," >> tpccbp_f1.txt
    done
    echo -n -e "\n"  >> tpccbp_f1.txt
done

for i in $THREADS
do
    for t in $PTMLIB
    do
        echo "Running TPCC (Bplustree) with $t and $i threads ..."
        numactl -N 0 ./obj64/tpcc_B+_$t -d 5 -t $i >> tpccbp_f2.txt
        echo -n "," >> tpccbp_f2.txt
    done
    echo -n -e "\n"  >> tpccbp_f2.txt
done
