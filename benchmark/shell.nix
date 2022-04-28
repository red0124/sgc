with import <nixpkgs> {}; {
  qpidEnv = stdenvNoCC.mkDerivation {
    name = "my_compiler_env";
    buildInputs = [
      hyperfine
      clang_14
      gcc11
    ];
  };
}
