#!/bin/awk -f
#
# Extract the primary trajectory from log file of a
#
#    mu2e -c ExtinctionMonitorFNALMC/test/trajectoryIn.fcl > out.log
#
# job.  Usage:
#
#    ./ExtinctionMonitorFNALMC/test/extractTrajectory.awk  out.log | tac
#
# A. Gaponenko, 2017

/^Pre:/ {
    printf( $3"\t"$4"\t"$5"\t%8.6f\t%8.6f\n", -$6/$8, -$7/$8);
}
