#pragma once
#include <string>
#include <ctime>
#include <mutex>

using namespace std;

const static int kMaxSiteNum = 1 << 16;

static mutex s_mutex[kMaxSiteNum];


struct SiteValue {
	int id;
	int x;
	int y;
	int tu;

	SiteValue() = default;

	SiteValue(int id, int x, int y, int tu) : id(id), x(x), y(y), tu(tu) {}
};

__declspec(align(32)) struct Site {
	__m128i content;

	Site() = default;

	Site(int id, int x, int y) {
		content = _mm_set_epi32(id, x, y, static_cast<int>(time(nullptr)));
	}

	SiteValue Value() const {
		return SiteValue(_mm_extract_epi32(content, 3),
		                 _mm_extract_epi32(content, 2),
		                 _mm_extract_epi32(content, 1),
		                 _mm_extract_epi32(content, 0));
	}

	void SetTime(int tu) {
		__m128i c = _mm_load_si128(&content);
		content = _mm_set_epi32(_mm_extract_epi32(c, 3),
		                        _mm_extract_epi32(c, 2),
		                        _mm_extract_epi32(c, 1),
		                        tu);
	}

	void SetValue(int x, int y, int tu) {
		content = _mm_set_epi32(_mm_extract_epi32(content, 3), x, y, tu);
	}

	void SetValue(int id, int x, int y, int tu) {
		content = _mm_set_epi32(id, x, y, tu);
	}

	void NegateTime() {
		__m128i c = _mm_load_si128(&content);
		content = _mm_set_epi32(_mm_extract_epi32(c, 3),
		                        _mm_extract_epi32(c, 2),
		                        _mm_extract_epi32(c, 1),
		                        -_mm_extract_epi32(c, 0));
	}

	int id() const {
		return _mm_extract_epi32(content, 3);
	}

	int tu() const {
		return _mm_extract_epi32(content, 0);
	}
};

