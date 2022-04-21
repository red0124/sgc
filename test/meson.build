unity_proj = subproject('unity')
unity_dep = unity_proj.get_variable('unity_dep')

tests = [
  ['ALGORITHM', 'algorithm'],
  ['DEQUE', 'deque'],
  ['FORWARD_LIST', 'forward_list'],
  ['LIST', 'list'],
  ['MAP', 'map'],
  ['PRIORITY_QUEUE', 'priority_queue'],
  ['QUEUE', 'queue'],
  ['SET', 'set'],
  ['STACK', 'stack'],
  ['STRING', 'string'],
  ['UNORDERED_MAP', 'unordered_map'],
  ['UNORDERED_SET', 'unordered_set'],
  ['VECTOR', 'vector'],
  ['FS_DEQUE', 'fs_deque'],
  ['FS_PRIORITY_QUEUE', 'fs_priority_queue'],
  ['FS_QUEUE', 'fs_queue'],
  ['FS_STACK', 'fs_stack'],
  ['FS_UNORDERED_MAP', 'fs_unordered_map'],
  ['FS_UNORDERED_SET', 'fs_unordered_set'],
  ['FS_VECTOR', 'fs_vector'],
  ['UTILS', 'utils'],
  ]

foreach name_file : tests
  name = name_file[0]
  file = name_file[1]

  exe = executable(
    name,
    'test_' + file + '.c',
    dependencies: [unity_dep, sgc_dep]
    )

  test(name, exe)
endforeach
