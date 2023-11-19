# Maintainer: hashpad <hashpad@proton.me>
pkgname=qomodoro
pkgver=1.0.0
pkgrel=1
pkgdesc="A Pomodoro timer application written in Qt" 
arch=('x86_64')
license=('GPL')
depends=(qt6-charts qt6-base cmake make qt6-multimedia)
makedepends=(cmake make)
source=("git+https://github.com/hashpad/Qomodoro")
noextract=()
md5sums=('SKIP')


build() {
	mkdir "$pkgname-$pkgver" -p
	mv Qomodoro/* "$pkgname-$pkgver"
	rm -rf Qomodoro
	cd "$pkgname-$pkgver"
	mkdir -p build
	cd build
	cmake ..
	make
}

package() {
	cd "$pkgname-$pkgver/build"
	make DESTDIR="$pkgdir/" install
	install -Dm644 "$srcdir/$pkgname-$pkgver/$pkgname.desktop" "$pkgdir/usr/share/applications/$pkgname.desktop"
}

