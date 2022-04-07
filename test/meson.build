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
  ['STATIC_DEQUE', 'static_deque'],
  ['STATIC_PRIORITY QUEUE', 'static_priority_queue'],
  ['STATIC_QUEUE', 'static_queue'],
  ['STATIC_STACK', 'static_stack'],
  ['STATIC_UNORDERED_MAP', 'static_unordered_map'],
  ['STATIC_UNORDERED_SET', 'static_unordered_set'],
  ['STATIC_VECTOR', 'static_vector'],
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
