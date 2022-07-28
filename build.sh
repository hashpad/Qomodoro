CMAKE_PREFIX_PATH=$HOME/Qt/6.3.1/gcc_64/
BEAR=`bear --append -- `

NPROC=`nproc --all`
CORES=$NPROC

OUTPUT=bin

MAKE=`make -j${CORES}`

[ ! -d $OUTPUT ] && mkdir $OUTPUT
(cd $OUTPUT; $BEAR cmake ..; $BEAR $MAKE)

[ -f $OUTPUT/compile_commands.json ] && cp $OUTPUT/compile_commands.json .

[[ $1 -eq "run" ]] && ./$OUTPUT/Qomodoro
