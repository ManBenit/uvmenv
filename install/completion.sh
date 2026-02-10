# uvmenv command structure:
#   uvmenv ctx opt comp name mtyp attr
# where:
#   ctx  : Project or component lever, or initial project options
#   opt  : Project or component specific options
#   comp : UVM component (e.g., agent, seqitem, seqce, env, test, etc.)
#   name : Look for specific filename into its component directory
#   mtyp : Module or type (depending on create or delete option for components)
#   attr : Standard (s), active (a) or passive (p), only for agents.




_uvmenv(){
    local cur prev ctx opt comp name mtyp attr
    
    local ctx_values=("new" "search" "help" "project" "component")
    
    local opt_values_proj=("init" "view" "run" "wave" "report")
    local opt_values_comp=("create" "delete" "list" "edit")

    local comp_values_gral=("agent" "seqitem" "seqce" "scorebd" "refmod" "bfm" "misc")
    local comp_values_edit=("top" "test" "env" "config" "util" "path")
    local comp_values_list=("rtlsig" "rtlmod")
    local edit_options=("${comp_values_gral[@]}" "${comp_values_edit[@]}")
    local list_options=("${comp_values_gral[@]}" "${comp_values_list[@]}")

    local mtyp_agent_values=("drv" "mon" "cc")
    local mtyp_seqitem_values=("req" "res")


    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    ctx="${COMP_WORDS[1]}"
    opt="${COMP_WORDS[2]}"
    comp="${COMP_WORDS[3]}"
    name="${COMP_WORDS[4]}"
    mtyp="${COMP_WORDS[5]}"
    attr="${COMP_WORDS[6]}"

    # If word starts with '-', suggest options
    #if [[ ${cur} == -* ]] ; then
    #    COMPREPLY=( $(compgen -W "${opt_values[*]}" -- ${cur}) )
    #    return 0
    #fi

    # ctx
    if [[ $COMP_CWORD -eq 1 ]] ; then
        COMPREPLY=( $(compgen -W "${ctx_values[*]}" -- ${cur}) )
        return 0
    fi

    # opt
    if [[ $COMP_CWORD -eq 2 ]] ; then
        case "$ctx" in
            project)
                COMPREPLY=( $(compgen -W "${opt_values_proj[*]}" -- "${cur}") )
                ;;
            component)
                COMPREPLY=( $(compgen -W "${opt_values_comp[*]}" -- "${cur}") )
                ;;
            *)
                # Si ctx es 'new', 'search' o 'help', podrías añadir opciones aquí
                ;;
        esac
        return 0
    fi

    if [[ ${COMP_CWORD} -eq 3 ]] ; then
        if [[ "$ctx" == "component" ]] ; then
            case "$opt" in
                edit)
                    COMPREPLY=( $(compgen -W "${edit_options[*]}" -- "$cur") )
                    ;;
                list)
                    COMPREPLY=( $(compgen -W "${list_options[*]}" -- "$cur") )
                    ;;
                *)
                    COMPREPLY=( $(compgen -W "${comp_values_gral[*]}" -- "$cur") )
                    ;;
            esac
        fi
        return 0
    fi

    if [[ ${COMP_CWORD} -eq 4 ]] ; then
        if [[ "$opt" != "list" ]]; then
            # Suggest filenames only for 'create' and 'delete' options
            COMPREPLY=("SEARCH_INTO_COMPONENT_DIRECTORY")
            return 0
            if [[ "$opt" == "create" || "$opt" == "delete" ]] ; then
                local dir_path=""
                case "$comp" in
                    agent|seqitem|seqce|scorebd|refmod|bfm|misc)
                        dir_path="components/${comp}/"
                        ;;
                    top|test|env|config|util|path)
                        dir_path="components/${comp}/"
                        ;;
                    rtlsig|rtlmod)
                        dir_path="rtl/${comp}/"
                        ;;
                    *)
                        dir_path=""
                        ;;
                esac

                if [[ -n "$dir_path" && -d "$dir_path" ]] ; then
                    local files=($(ls "${dir_path}"))
                    COMPREPLY=( $(compgen -W "${files[*]}" -- "$cur") )
                fi
            fi
        fi
    fi

    if [[ ${COMP_CWORD} -eq 5 ]] ; then
        case "$opt" in
            create)
                if [[ "$comp" == "agent" ]] || [[ "$comp" == "seqitem" ]] ; then
                    COMPREPLY=("DO_showModules_MECHANISM")
                else
                    COMPREPLY=()
                fi
                ;;
            edit)
                case "$comp" in
                        agent)
                            COMPREPLY=( $(compgen -W "${mtyp_agent_values[*]}" -- "${cur}") )
                            ;;
                        seqitem)
                            COMPREPLY=( $(compgen -W "${mtyp_seqitem_values[*]}" -- "${cur}") )
                            ;;
                        *)
                            COMPREPLY=()
                            ;;
                esac
                ;;
            *)
                # Si ctx es 'new', 'search' o 'help', podrías añadir opciones aquí
                ;;
        esac
        return 0
    fi

    if [[ ${COMP_CWORD} -eq 6 ]] ; then
        if [[ "$opt" == "create" ]] && [[ "$comp" == "agent" ]] ; then
            COMPREPLY=( $(compgen -W "s a p" -- "${cur}") )
        fi
        return 0
    fi
}

complete -F _uvmenv uvmenv

