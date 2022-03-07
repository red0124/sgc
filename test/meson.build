unity_proj = subproject('unity')
unity_dep = unity_proj.get_variable('unity_dep')

tests = [
  ['ALGORITHM', 'algorithm'],
  ['DEQUE', 'deque'],
  ['FORWARD LIST', 'forward_list'],
  ['LIST', 'list'],
  ['MAP', 'map'],
  ['PRIORITY QUEUE', 'priority_queue'],
  ['QUEUE', 'queue'],
  ['SET', 'set'],
  ['STACK', 'stack'],
  ['STRING', 'string'],
  ['UNORDERED MAP', 'unordered_map'],
  ['UNORDERED SET', 'unordered_set'],
  ['VECTOR', 'vector'],
  ['STATIC DEQUE', 'static_deque'],
  ['STATIC FORWARD LIST', 'static_forward_list'],
  ['STATIC LIST', 'static_list'],
  ['STATIC MAP', 'static_map'],
  ['STATIC PRIORITY QUEUE', 'static_priority_queue'],
  ['STATIC QUEUE', 'static_queue'],
  #['STATIC SET', 'static_set'],
  ['STATIC STACK', 'static_stack'],
  ['STATIC UNORDERED MAP', 'static_unordered_map'],
  ['STATIC UNORDERED SET', 'static_unordered_set'],
  ['STATIC VECTOR', 'static_vector'],
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
