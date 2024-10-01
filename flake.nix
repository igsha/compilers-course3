{
  description = "compilers-course3";

  inputs.nixpkgs.url = github:nixos/nixpkgs?ref=nixos-unstable;

  outputs = { self, nixpkgs }: let
    pkgs = nixpkgs.legacyPackages.x86_64-linux.pkgs;
    llvmStdenv = pkgs.llvmPackages_18.libcxxStdenv;
  in {
    devShells.x86_64-linux.default = with pkgs; (mkShell.override { stdenv = llvmStdenv; }) {
      packages = [ gdb valgrind ninja cmake ];
      hardeningDisable = [ "all" ];
      CXXFLAGS = builtins.concatStringsSep " " [
        (lib.removeSuffix "\n" (builtins.readFile "${llvmStdenv.cc}/nix-support/libc-cflags"))
        (lib.removeSuffix "\n" (builtins.readFile "${llvmStdenv.cc}/nix-support/libcxx-cxxflags"))
      ];
      CMAKE_GENERATOR = "Ninja";
    };
  };
}
