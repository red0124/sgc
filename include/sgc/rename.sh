#!/bin/bash

FILE="priority_queue.h static_priority_queue.h detail/sgc_priority_queue_common.h"
KEYS=("N##_resize" "N##_memswp" "N##_fix_insert" \
    "N##_fix_erase" \
    "N##_corect" "N##_check" "N##_insert_node" "N##_insert_or_get_node" \
    "N##_find_node" "N##_erase_rebalanse" "N##_erase_node" \
    "N##_copy_node_values" "N##_duplicate_node" "N##_copy_base_data" \
    "N##_copy_nodes"  "N##_free_node")

REPLACEMENTS=("_m_##N##_node" "_m_##N##_stack_size" "_m_##N##_is_left_child" \
    "_m_##N##_resize" "_m_##N##_memswap" "_m_##N##_fix_insert" \
    "_m_##N##_fix_erase" \
    "_m_##N##_node_insert_or_get" "_m_##N##_node_find" \
    "_m_##N##_erase_rebalanse" "_m_##N##_node_erase" "_m_##N##_node_copy_values" \
    "_m_##N##_node_duplicate" "_m_##N##_copy_base_data" "_m_##N##_copy_nodes" \
    "_m_##N##_node_free")

for file in $FILE; do
    echo $file
    for i in ${!KEYS[@]}; do
        sed "s/${KEYS[$i]}/${REPLACEMENTS[$i]}/g" -i $file
    done
done
