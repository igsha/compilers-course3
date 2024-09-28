{
  description = "compilers-course3";

  inputs.nixpkgs.url = github:nixos/nixpkgs?ref=nixos-unstable;

  outputs = { self, nixpkgs }: let
    pkgs = nixpkgs.legacyPackages.x86_64-linux.pkgs;
  in {
    devShells.x86_64-linux.default = with pkgs; mkShell {
      packages = [ gdb valgrind ninja cmake ];
      hardeningDisable = [ "all" ];
    };
  };
}
