"""Generates every PNG in Texture/ (cards, table, panels, banners).
Run from the project folder:  python tools/gen_textures.py
Needs Pillow and the DejaVu Sans fonts (any bold/regular TTF with card suits works)."""
import math
import os
from PIL import Image, ImageDraw, ImageFont

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "Texture")
CARDS = os.path.join(ROOT, "cards")
FONT_B = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"
FONT_R = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"
os.makedirs(CARDS, exist_ok=True)

SS = 4  # supersampling factor for smooth edges
RANKS = "23456789TJQKA"
SUITS = "shdc"  # same order as enum class Suit {Spade, Heart, Diamond, Club}
GLYPH = {"s": "\u2660", "h": "\u2665", "d": "\u2666", "c": "\u2663"}
RED = (205, 36, 48, 255)
BLACK = (24, 28, 40, 255)


def font(path, size):
    return ImageFont.truetype(path, max(1, int(size)))


def save(img, path):
    img.save(path)


def rounded(w, h, radius, fill, outline=None, width=0):
    img = Image.new("RGBA", (w * SS, h * SS), (0, 0, 0, 0))
    d = ImageDraw.Draw(img)
    d.rounded_rectangle([0, 0, w * SS - 1, h * SS - 1], radius=radius * SS, fill=fill,
                        outline=outline, width=width * SS)
    return img.resize((w, h), Image.LANCZOS)


def card_face(rank, suit, w, h):
    img = Image.new("RGBA", (w * SS, h * SS), (0, 0, 0, 0))
    d = ImageDraw.Draw(img)
    s = w / 64.0
    d.rounded_rectangle([0, 0, w * SS - 1, h * SS - 1], radius=int(8 * s * SS),
                        fill=(250, 250, 248, 255), outline=(110, 116, 128, 255),
                        width=max(1, int(2 * s * SS)))
    color = RED if suit in "hd" else BLACK
    label = "10" if rank == "T" else rank
    f_rank = font(FONT_B, (h * 0.27 if rank != "T" else h * 0.23) * SS)
    f_small = font(FONT_R, h * 0.20 * SS)
    f_big = font(FONT_R, h * 0.50 * SS)
    d.text((6 * s * SS, 3 * s * SS), label, font=f_rank, fill=color, anchor="la")
    d.text((6 * s * SS, h * 0.30 * SS), GLYPH[suit], font=f_small, fill=color, anchor="la")
    d.text((w * 0.52 * SS, h * 0.64 * SS), GLYPH[suit], font=f_big, fill=color, anchor="mm")
    return img.resize((w, h), Image.LANCZOS)


def card_back(w, h):
    img = Image.new("RGBA", (w * SS, h * SS), (0, 0, 0, 0))
    d = ImageDraw.Draw(img)
    s = w / 64.0
    d.rounded_rectangle([0, 0, w * SS - 1, h * SS - 1], radius=int(8 * s * SS),
                        fill=(236, 238, 244, 255), outline=(110, 116, 128, 255),
                        width=max(1, int(2 * s * SS)))
    m = int(4 * s * SS)
    d.rounded_rectangle([m, m, w * SS - 1 - m, h * SS - 1 - m], radius=int(5 * s * SS),
                        fill=(28, 58, 140, 255))
    step = int(10 * s * SS)
    inner = [m, m, w * SS - 1 - m, h * SS - 1 - m]
    lat = Image.new("RGBA", img.size, (0, 0, 0, 0))
    ld = ImageDraw.Draw(lat)
    for k in range(-h * SS, w * SS + h * SS, step):
        ld.line([(k, 0), (k + h * SS, h * SS)], fill=(90, 130, 220, 150), width=max(1, int(s * SS)))
        ld.line([(k, h * SS), (k + h * SS, 0)], fill=(90, 130, 220, 150), width=max(1, int(s * SS)))
    mask = Image.new("L", img.size, 0)
    ImageDraw.Draw(mask).rounded_rectangle(inner, radius=int(5 * s * SS), fill=255)
    img.paste(lat, (0, 0), Image.composite(lat.split()[3], Image.new("L", img.size, 0), mask))
    d.rounded_rectangle(inner, radius=int(5 * s * SS), outline=(200, 215, 255, 255),
                        width=max(1, int(2 * s * SS)))
    return img.resize((w, h), Image.LANCZOS)


def card_empty(w, h):
    return rounded(w, h, 8, (255, 255, 255, 22), (255, 255, 255, 70), 2)


def card_flip(w, h):
    img = Image.new("RGBA", (w, h), (0, 0, 0, 0))
    sliver = rounded(10, h, 3, (245, 245, 245, 255), (110, 116, 128, 255), 1)
    img.paste(sliver, ((w - 10) // 2, 0), sliver)
    return img


def circle(size, fill, outline=None, width=0):
    img = Image.new("RGBA", (size * SS, size * SS), (0, 0, 0, 0))
    ImageDraw.Draw(img).ellipse([0, 0, size * SS - 1, size * SS - 1], fill=fill, outline=outline,
                                width=width * SS)
    return img


def chip(size=24):
    img = circle(size, (200, 48, 60, 255), (255, 255, 255, 255), 2)
    d = ImageDraw.Draw(img)
    c = size * SS / 2
    for k in range(8):
        a = k * math.pi / 4
        x0, y0 = c + math.cos(a) * c * 0.72, c + math.sin(a) * c * 0.72
        x1, y1 = c + math.cos(a) * c * 0.95, c + math.sin(a) * c * 0.95
        d.line([(x0, y0), (x1, y1)], fill=(255, 255, 255, 255), width=int(2.5 * SS))
    d.ellipse([c - c * 0.45, c - c * 0.45, c + c * 0.45, c + c * 0.45], outline=(255, 220, 220, 255),
              width=SS)
    return img.resize((size, size), Image.LANCZOS)


def dealer(size=26):
    img = circle(size, (250, 250, 250, 255), (30, 30, 30, 255), 2)
    ImageDraw.Draw(img).text((size * SS / 2, size * SS / 2 + SS), "D", font=font(FONT_B, size * 0.62 * SS),
                             fill=(20, 20, 20, 255), anchor="mm")
    return img.resize((size, size), Image.LANCZOS)


def lerp(a, b, t):
    return tuple(int(a[i] + (b[i] - a[i]) * t) for i in range(len(a)))


def vertical_gradient(w, h, top, bottom):
    img = Image.new("RGB", (w, h))
    d = ImageDraw.Draw(img)
    for y in range(h):
        d.line([(0, y), (w, y)], fill=lerp(top, bottom, y / (h - 1)))
    return img


def table_image():
    w, h, k = 1280, 720, 2
    img = vertical_gradient(w * k, h * k, (14, 18, 30), (8, 10, 18)).convert("RGBA")
    d = ImageDraw.Draw(img)
    cx, cy = 640 * k, 345 * k
    rx, ry = 600 * k, 300 * k
    d.ellipse([cx - rx - 8 * k, cy - ry - 8 * k + 10 * k, cx + rx + 8 * k, cy + ry + 8 * k + 10 * k],
              fill=(0, 0, 0, 110))
    d.ellipse([cx - rx, cy - ry, cx + rx, cy + ry], fill=(82, 48, 26, 255), outline=(40, 22, 12, 255),
              width=3 * k)
    d.ellipse([cx - rx + 8 * k, cy - ry + 8 * k, cx + rx - 8 * k, cy + ry - 8 * k], outline=(140, 92, 52, 255),
              width=2 * k)
    frx, fry = rx - 22 * k, ry - 22 * k
    steps = 60
    for i in range(steps):
        t = i / (steps - 1)
        col = lerp((14, 70, 50, 255), (30, 118, 82, 255), t)
        sx, sy = frx * (1 - t * 0.85), fry * (1 - t * 0.85)
        d.ellipse([cx - sx, cy - sy, cx + sx, cy + sy], fill=col)
    d.ellipse([cx - frx + 18 * k, cy - fry + 18 * k, cx + frx - 18 * k, cy + fry - 18 * k],
              outline=(214, 182, 96, 150), width=2 * k)
    mark = Image.new("RGBA", img.size, (0, 0, 0, 0))
    ImageDraw.Draw(mark).text((cx, cy + 62 * k), "DEEP STACK HOLD'EM", font=font(FONT_B, 28 * k),
                              fill=(255, 255, 255, 34), anchor="mm")
    img = Image.alpha_composite(img, mark)
    return img.resize((w, h), Image.LANCZOS).convert("RGB")


def paste_rotated(base, tile, center, angle):
    r = tile.rotate(angle, expand=True, resample=Image.BICUBIC)
    base.paste(r, (int(center[0] - r.width / 2), int(center[1] - r.height / 2)), r)


def title_bg():
    w, h = 1280, 720
    img = vertical_gradient(w, h, (18, 70, 54), (6, 22, 24)).convert("RGBA")
    d = ImageDraw.Draw(img)
    d.rounded_rectangle([24, 24, w - 25, h - 25], radius=26, outline=(214, 182, 96, 200), width=3)
    for center, cards in (((190, 420), ["As", "Ks"]), ((1090, 420), ["Ah", "Ad"])):
        for i, code in enumerate(cards):
            face = card_face(code[0], code[1], 128, 180)
            paste_rotated(img, face, (center[0] + (i * 70 - 35), center[1] + abs(i * 70 - 35) * 0.2),
                          18 - i * 36 if center[0] < 640 else 18 - i * 36)
    d.text((641, 91), "TEXAS HOLD'EM", font=font(FONT_B, 92), fill=(0, 0, 0, 160), anchor="mm")
    d.text((640, 88), "TEXAS HOLD'EM", font=font(FONT_B, 92), fill=(255, 214, 120, 255), anchor="mm")
    d.text((640, 168), "D E E P   S T A C K", font=font(FONT_B, 42), fill=(220, 236, 232, 255), anchor="mm")
    return img.convert("RGB")


def howto_bg():
    w, h = 1280, 720
    img = vertical_gradient(w, h, (14, 20, 34), (8, 12, 22)).convert("RGBA")
    panel = rounded(1100, 600, 24, (10, 16, 28, 235), (214, 182, 96, 230), 3)
    img.paste(panel, (90, 60), panel)
    ImageDraw.Draw(img).text((640, 108), "HOW TO PLAY", font=font(FONT_B, 48), fill=(255, 214, 120, 255),
                             anchor="mm")
    return img.convert("RGB")


def plate(border, fill=(18, 24, 38, 225), bw=2):
    return rounded(200, 62, 12, fill, border, bw)


def banner(text, color, sub):
    img = rounded(520, 170, 22, (8, 12, 22, 240), color, 4)
    d = ImageDraw.Draw(img)
    d.text((260, 60), text, font=font(FONT_B, 62), fill=color, anchor="mm")
    d.text((260, 108), sub, font=font(FONT_R, 20), fill=(190, 205, 222, 255), anchor="mm")
    return img


def main():
    for r in RANKS:
        for s in SUITS:
            save(card_face(r, s, 64, 90), os.path.join(CARDS, "L_%s%s.png" % (r, s)))
            save(card_face(r, s, 44, 62), os.path.join(CARDS, "S_%s%s.png" % (r, s)))
    save(card_back(64, 90), os.path.join(CARDS, "L_back.png"))
    save(card_back(44, 62), os.path.join(CARDS, "S_back.png"))
    save(card_empty(64, 90), os.path.join(CARDS, "L_empty.png"))
    save(card_flip(44, 62), os.path.join(CARDS, "S_flip.png"))

    save(table_image(), os.path.join(ROOT, "table.png"))
    save(title_bg(), os.path.join(ROOT, "title_bg.png"))
    save(howto_bg(), os.path.join(ROOT, "howto_bg.png"))

    art = Image.open(os.path.join(ROOT, "a.png")).convert("RGBA")
    save(art.resize((art.width * 3, art.height * 3), Image.NEAREST), os.path.join(ROOT, "title_art.png"))

    save(plate((74, 88, 114, 255)), os.path.join(ROOT, "plate_normal.png"))
    save(plate((72, 202, 228, 255), bw=3), os.path.join(ROOT, "plate_you.png"))
    save(plate((255, 209, 102, 255), (40, 34, 14, 235), 4), os.path.join(ROOT, "plate_active.png"))
    save(plate((112, 224, 0, 255), (16, 44, 20, 235), 4), os.path.join(ROOT, "plate_winner.png"))
    save(plate((50, 58, 72, 255), (18, 24, 38, 130), 2), os.path.join(ROOT, "plate_dim.png"))

    panel_fill, panel_line = (8, 12, 22, 215), (84, 98, 124, 255)
    save(rounded(340, 112, 12, panel_fill, panel_line, 2), os.path.join(ROOT, "panel_log.png"))
    save(rounded(494, 112, 12, panel_fill, panel_line, 2), os.path.join(ROOT, "panel_action.png"))

    save(chip(24), os.path.join(ROOT, "chip.png"))
    save(dealer(26), os.path.join(ROOT, "dealer.png"))
    save(banner("YOU WIN!", (255, 214, 102, 255), "Every opponent is out of chips"),
         os.path.join(ROOT, "banner_win.png"))
    save(banner("BUSTED", (255, 107, 107, 255), "You ran out of chips"),
         os.path.join(ROOT, "banner_lose.png"))


if __name__ == "__main__":
    main()
