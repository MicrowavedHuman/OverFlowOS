#!/bin/bash
set -e

KERNEL="$(pwd)/OverFlowOS"
ISO_DIR="$(pwd)/isodir"
ISO_NAME="$(pwd)/OverFlowOS.iso"

echo "[+] Working directory:"
pwd

echo "[+] Checking kernel..."

if [ ! -f "$KERNEL" ]; then
    echo "[!] Kernel not found: $KERNEL"
    exit 1
fi

echo "[+] Creating ISO directory..."

rm -rf "$ISO_DIR"
mkdir -p "$ISO_DIR/boot/grub"

echo "[+] Copying kernel..."

cp "$KERNEL" "$ISO_DIR/boot/OverFlowOS"

echo "[+] Writing grub.cfg..."

cat > "$ISO_DIR/boot/grub/grub.cfg" <<EOF
set timeout=0
set default=0

menuentry "OverFlowOS" {
    multiboot /boot/OverFlowOS
    boot
}
EOF

echo "[+] ISO tree:"
find "$ISO_DIR"

echo "[+] Building ISO..."

grub-mkrescue -o "$ISO_NAME" "$ISO_DIR"

echo "[+] Created:"
echo "$ISO_NAME"
