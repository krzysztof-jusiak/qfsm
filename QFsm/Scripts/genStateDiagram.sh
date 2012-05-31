#!/bin/sh

#OLD version -> will be replaced with genStateDiagram.sh
#gen-state-diagram.sh Player `find . -iname *.hpp`
#Playing [image="Playing.png" label=""] }

#[ $# -ne 2 ] &&
    #echo -e "usage:\n\
        #$0 file FsmClass\n\
        #$0 file.hpp FsmClass | dot -Tpng -o output.png\n\
        #colors=\"black\" $0 file.hpp FsmClass \n\
        #colors=\"red blue\" directions=\"nswe\" $0 file.hpp FsmClass"\
    #&& exit -1;

#[ ! -e $1 ] &&
    #echo "file \"$1\" not exits" && exit -1;

get_param()
{
    cb=0
    pos=0
    param=1

    for ((i=0; i < ${#1}; ++i)); do
        case ${1:i:1} in
          "<") ((cb++)) ;;
          ">") ((cb--)) ;;
          ",")
            if [ $cb -eq 0 ]; then
                [ $2 -eq $param ] && echo ${1:pos:$((i-pos))}
                pos=$((i+1))
                ((param++))
            fi ;;
        esac
    done
}

update_braces_count()
{
    value=0
    for ((i=0; i < ${#1}; ++i)); do
        case ${1:i:1} in
          "{") ((value++)) ;;
          "}") ((value--)) ;;
        esac
    done

    echo $value;
}

generate_dot_state_diagram()
{
    FILE=$1
    FSM=$2

    rm -f /tmp/*.state 2>/dev/null

    echo "
    digraph {
        labeljust=l;
        labelloc=t;
        label=\"$FILE/$FSM\";
        graph [fontsize=10];
        edge [fontsize=8];
        node [shape=box, style=rounded, fontsize=10];
        start [shape=circle, label=\"\", style=filled];
    ";

    [ "$colors" ] || colors="red green blue brown black"
    [ "$directions" ] || directions="ews"

    dindex=0;
    cindex=0;
    braces=0
    abraces=0
    found=no
    colorsl=($colors);
    result=0

    while read line; do
        if [ "$found" == "no" ] && [ "`echo $line | grep \"class.*$FSM\"`" != "" ]; then
            found=yes
            abraces=$braces
        elif [ "$found" == "done" ] && [ $braces -le $abraces ]; then
            break
        fi

        ((braces+=`update_braces_count "$line"`));

        if [ $braces -eq $((abraces+1)) ] && [ "`echo $line | grep InitialState`" != "" ]; then
            echo "start -> `echo $line | grep InitialState | awk '{print $2}'`"
        elif [ $braces -eq $((abraces+1)) ] && [ "`echo $line | grep 'Transition.*<'`" != "" ]; then
            found=done
            result=1

            line=`echo $line | sed 's/.*Transition[^<]*<\(.*\)>.*/\1,/'`

            InitState=`get_param "$line" 1`
            Event=`get_param "$line" 2`
            Guard=; [ "`get_param "$line" 3`" != "None" ] && Guard="[`get_param "$line" 3`]"
            Action=;[ "`get_param "$line" 4`" != "None" ] && Action="/`get_param "$line" 4`()"
            TargetState=`get_param "$line" 5`

            if [ "`echo $line | grep OnEntry`" != "" ]; then
                echo -n "OnEntry $Guard$Action\n" >> /tmp/$InitState.state
            elif [ "`echo $line | grep OnExit`" != "" ]; then
                echo -n "OnExit $Guard$Action\n" >> /tmp/$InitState.state
            else
                [ $dindex -ge ${#directions} ] && ((dindex=0))
                [ $cindex -ge ${#colorsl[@]} ] && ((cindex=0))
                color=${colorsl[((cindex++))]}
                echo "$InitState -> $TargetState:${directions:((dindex++)):1} [color=\"$color\" fontcolor=\"$color\" label=\"$Event\n$Guard$Action\"];"
            fi
        fi
    done < $FILE

    for file in `ls /tmp/*.state 2>/dev/null`; do
        echo `basename $file | cut -d . -f1` "[label=\"`cat $file`\"]"
    done

    echo "}";

    rm -f /tmp/*.state 2>/dev/null

    return $result;
}

generate_image_state_diagram()
{
    echo searching for \"$2\" in $1...

    diagram=`generate_dot_state_diagram $1 $2`

    if [ $? -eq 1 ]; then
        echo $diagram | dot -Tpng -o $2.png
        echo \"$2.png\" generated
        return 1;  #generated
    fi

    return 0; #not generated
}

search_and_generate_image_state_diagram()
{
    FSM=$1
    for file in `find ${@:2} -iname "*.hpp" -or -iname "*.cpp"`; do
        generate_image_state_diagram $file $FSM
        [ $? -eq 1 ] && break;
    done
}

search_and_generate_image_state_diagram $1 ${@:2}

