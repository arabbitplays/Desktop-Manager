{
  description = "DesktopManager flake with devShell and build derivation";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
  };

  outputs = { self, nixpkgs }: let
    systems = [ "x86_64-linux" "aarch64-linux" ];
    forAllSystems = nixpkgs.lib.genAttrs systems;
  in
  {
    # Development shells
    devShells = forAllSystems (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        default = pkgs.mkShell {
          packages = with pkgs; [];

          buildInputs = with pkgs; [
            meson
            ninja
            pkg-config
            python3
          ];

          shellHook = ''
            echo "Entered DesktopManager dev environment for ${system}"
          '';
        };
      }
    );

    # Packages / build derivation
    packages = forAllSystems (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        desktop-manager = pkgs.stdenv.mkDerivation {
          pname = "DesktopManager";
          version = "1.0.0";

          src = pkgs.fetchgit {
            url = "https://github.com/arabbitplays/Desktop-Manager";
            sha256 = "FVIKafe4D+dlT2IOFGZ+Cd9nHIbqW+BVsPgChJXsis8=";
          };

          nativeBuildInputs = with pkgs; [
            meson
            ninja
            pkg-config
          ];

          buildInputs = with pkgs; [
            python3
          ];

          buildPhase = ''
            meson setup build --prefix=$out
            meson compile -C build
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp build/DesktopManager $out/bin/DesktopManager
          '';
        };
      }
    );

    # Default package for `nix run .`
    defaultPackage = self.packages.${builtins.currentSystem}.desktop-manager;
  };
}
