[[ $1 == "clean" ]] && rm -rf ./bin compile_commands* && exit
BEAR="bear --append --"

NPROC=`nproc --all`
CORES=$NPROC

OUTPUT=bin


[ ! -d $OUTPUT ] && mkdir $OUTPUT
(cd $OUTPUT; $BEAR cmake ..; $BEAR make -j${CORES})

[ -f $OUTPUT/compile_commands.json ] && cp $OUTPUT/compile_commands.json .

[[ $1 == "run" ]] && ./$OUTPUT/Qomodoro
