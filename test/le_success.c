#include <assert.h>
#include <assertions.h>

int main() {
    assert(LE(0, 1));
    assert(LE(0, 0));
}
