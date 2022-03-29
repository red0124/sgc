#!/bin/bash

FILE="*.h detail/*.h"
KEYS=( \
    "xxxxxxxx" \
    "N##_bucket_end" \
    "N##_bucket_insert" \
    "N##_bucket_node_size" \
    "N##_bucket_remove" \
    "N##_bucket_sgc_free" \
    "N##_check_color" \
    "N##_compare_node" \
    "N##_copy_base_data" \
    "N##_copy_nodes" \
    "N##_correct_tree" \
    "N##_erase_rebalanse" \
    "N##_find_by_hash" \
    "N##_insert_multiple_node" \
    "N##_is_left_child" \
    "N##_iterator_max" \
    "N##_memswp" \
    "N##_move_back" \
    "N##_move" \
    "N##_node_alloc" \
    "N##_node_begin" \
    "N##_node_compare" \
    "N##_node_copy_values" \
    "N##_node_duplicate" \
    "N##_node_end" \
    "N##_node_equal_key" \
    "N##_node_erase" \
    "N##_node_find" \
    "N##_node_free" \
    "N##_node_hash_value" \
    "N##_node_insert" \
    "N##_node_new" \
    "N##_ptr_array_to_list" \
    "N##_qsort" \
    "N##_rehash_size" \
    "N##_resize" \
    "N##_rotate_left_right" \
    "N##_rotate_left" \
    "N##_rotate_right_left" \
    "N##_rotate_right" \
    "N##_rotate" \
    "N##_sibling" \
    "N##_stack_size" \
    "xxxxxxxx")

# ....!

REPLACEMENTS=( \
    "xxxxxxxx" \
    "_m_##N##_bucket_end" \
    "_m_##N##_bucket_insert" \
    "_m_##N##_bucket_node_size" \
    "_m_##N##_bucket_remove" \
    "_m_##N##_bucket_sgc_free" \
    "_m_##N##_check_color" \
    "_m_##N##_node_compare" \
    "_m_##N##_copy_base_data" \
    "_m_##N##_copy_nodes" \
    "_m_##N##_correct_tree" \
    "_m_##N##_erase_rebalanse" \
    "_m_##N##_find_by_hash" \
    "_m_##N##_node_insert_multiple" \
    "_m_##N##_is_left_child" \
    "_m_##N##_iterator_max" \
    "_m_##N##_memswp" \
    "_m_##N##_go_back" \
    "_m_##N##_go_forward" \
    "_m_##N##_node_alloc" \
    "_m_##N##_node_begin" \
    "_m_##N##_node_compare" \
    "_m_##N##_node_copy_values" \
    "_m_##N##_node_duplicate" \
    "_m_##N##_node_end" \
    "_m_##N##_node_equal_key" \
    "_m_##N##_node_erase" \
    "_m_##N##_node_find" \
    "_m_##N##_node_free" \
    "_m_##N##_node_hash_value" \
    "_m_##N##_node_insert" \
    "_m_##N##_node_new" \
    "_m_##N##_ptr_array_to_list" \
    "_m_##N##_qsort" \
    "_m_##N##_rehash_size" \
    "_m_##N##_resize" \
    "_m_##N##_rotate_left_right" \
    "_m_##N##_rotate_left" \
    "_m_##N##_rotate_right_left" \
    "_m_##N##_rotate_right" \
    "_m_##N##_rotate" \
    "_m_##N##_sibling" \
    "_m_##N##_stack_size" \
    "xxxxxxxx")

for file in $FILE; do
    echo $file
    for i in ${!KEYS[@]}; do
        sed "s/${KEYS[$i]}(/${REPLACEMENTS[$i]}(/g" -i $file
        clang-format -i $file
    done
done
