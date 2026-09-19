"""
cpp_bridge.py

MATHESIS.AM-ում Python-ի սկզբնական քայլը: Այս ֆայլն ինքը ոչինչ չի հաշվարկում.
այն պարզապես կանչում է արդեն գրված C++ engine-ը, կարդում նրա պատասխանը,
և վերադարձնում քեզ մաքուր Python dict:

Սա կոչվում է "subprocess" մոտեցում. Python-ը և C++-ը մնում են երկու
առանձին ծրագրեր, որոնք հաղորդակցվում են stdin/stdout-ով:

Ծանոթություն. փոփոխականների և ֆունկցիաների անունները մնում են անգլերեն
(ստանդարտ պրակտիկա է), բայց մեկնաբանությունները հայերեն են:

Աշխատացնել այսպես.  python3 python/bridge/cpp_bridge.py
"""

import subprocess
import json
import sys

# Ուղին compiled C++ engine-ին. ԿԱՐԵՎՈՐ. այս path-ը հարաբերական է այն
# folder-ին, որտեղից գործարկում ես python3-ը (ոչ թե այս ֆայլի տեղադրության
# նկատմամբ) — միշտ գործարկիր repo-ի root-ից:
ENGINE_PATH = "engine/build/math_engine"


def solve_with_cpp_engine(problem: str) -> dict:
    """
    Ուղարկում է `problem`-ը C++ engine-ին և վերադարձնում պատասխանը dict-ի
    տեսքով: Եթե ինչ-որ բան սխալ է գնում, բարձրացնում է RuntimeError:
    """
    try:
        result = subprocess.run(
            [ENGINE_PATH, problem],
            capture_output=True,
            text=True,
            timeout=10,  # մի հեռացրու սա. կախված engine-ը չպետք է կախի Python-ին
        )
    except FileNotFoundError:
        raise RuntimeError(
            f"Engine-ը չի գտնվել '{ENGINE_PATH}' ուղում. "
            "ստուգիր, որ C++ պրոեկտը build արված է։"
        )
    except subprocess.TimeoutExpired:
        raise RuntimeError("Engine-ը չափազանց երկար ժամանակ խնդրեց (>10 վրկ).")

    if result.returncode != 0:
        raise RuntimeError(f"Engine-ն ավարտվեց error-ով.\n{result.stderr}")

    try:
        return json.loads(result.stdout)
    except json.JSONDecodeError:
        return {"raw_output": result.stdout.strip()}


def main():
    problem = input("Մուտքագրիր խնդիրը. ").strip()
    if not problem:
        print("Ոչինչ չմուտքագրվեց.")
        sys.exit(1)

    try:
        result = solve_with_cpp_engine(problem)
    except RuntimeError as e:
        print(f"Սխալ. {e}")
        sys.exit(1)

    print(json.dumps(result, indent=2, ensure_ascii=False))


if __name__ == "__main__":
    main()