#include "../../../headers/uvmenv_handling/component_handling/list.h"


void showModules(){
    ////local modules_dir=($(find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \) | sort | uniq))
    //local modules_dir=($(find $DUT_HDL_DIR -type f \( -name "*.v" -o -name "*.sv" \) | sed -E 's/.*\/([^\/]+)\..*/\1/' | sort | uniq))
    ////readarray -t modules_dir <<< "$(ls -F $DUT_HDL_DIR | grep -v "/" | grep -E "sv|v")"

    /*for archivo in "${modules_dir[@]}"; do
        nom=$(echo $archivo | cut -d'.' -f1)
        if [ "$nom" == "$(jq -r '.dut_design.top_module' $CONFIG_FILE)" ]; then
            echo -e "${C_CYAN}$nom [Top]${C_N}"
        else
            echo "$nom"
        fi
    done*/
}