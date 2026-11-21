"""Guard the depth, navigation and runnable assets of the C17 curriculum."""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]
LEVELS = ("basics", "intermediate", "advanced")
LABS = ("checked_add", "parse_decimal", "text_buffer",
        "byte_histogram", "frame_header", "topological",
        "reverse_span", "parse_hex", "lower_bound",
        "unique_sorted", "ring_queue", "dag_distances")


class CurriculumCompleteness(unittest.TestCase):
    def test_all_thirty_six_chapters_are_substantive(self):
        for level in LEVELS:
            workshops = sorted(p for p in (ROOT / level).glob("*.md")
                               if p.name != "README.md")
            deep = sorted((ROOT / level / "deep-dives").glob("*.md"))
            self.assertEqual(len(workshops), 6, level)
            self.assertEqual(len(deep), 6, level)
            for chapter in deep:
                text = chapter.read_text(encoding="utf-8")
                self.assertGreaterEqual(
                    len(text.split()), 280,
                    f"Deep dive is too short: {chapter.relative_to(ROOT)}")
                self.assertIn("~~~c", text, chapter.name)
                self.assertIn("## ", text, chapter.name)
                self.assertIn("criterion", text.lower(), chapter.name)

    def test_workshops_projects_and_new_labs(self):
        for level in LEVELS:
            projects = list((ROOT / level / "projects").glob("*.md"))
            self.assertEqual(len(projects), 3, level)
            source = (ROOT / level / "README.md").read_text()
            self.assertIn("Professional deep dives", source)
            self.assertIn("mastery/README.md", source)
        for name in LABS:
            for bucket in ("starter", "reference"):
                path = ROOT / "mastery" / bucket / f"{name}.c"
                self.assertTrue(path.exists(), path)
                self.assertIn("#include \"mastery.h\"", path.read_text())
        self.assertTrue((ROOT / "mastery/include/mastery.h").exists())
        self.assertTrue((ROOT / "tests/mastery.c").exists())
        docs = sorted((ROOT / "mastery/tasks").glob("*.md"))
        self.assertEqual(len(docs), 12)
        for page in docs:
            text = page.read_text()
            self.assertGreater(len(text.split()), 200, page.name)
            self.assertIn("make mastery-check", text)
            self.assertIn("Interview", text)

    def test_three_capstones_have_acceptance_criteria(self):
        projects = ROOT / "mastery/projects"
        self.assertTrue((projects / "README.md").exists())
        project_files = sorted(projects.glob("[0-9][0-9]_*.md"))
        self.assertEqual(len(project_files), 3)
        for doc in project_files:
            text = doc.read_text()
            self.assertIn("Acceptance tests", text)
            self.assertIn("Review", text)
            self.assertGreater(len(text.split()), 300, doc.name)

    def test_roadmap_interviews_and_assessment(self):
        roadmap = (ROOT / "curriculum/ROADMAP.md").read_text()
        interview = (ROOT / "curriculum/INTERVIEW.md").read_text()
        assessment = (ROOT / "curriculum/ASSESSMENT.md").read_text()
        weeks = re.findall(r"(?m)^\| (?:[1-9]|1[0-2]) \|", roadmap)
        self.assertEqual(len(weeks), 12)
        questions = re.findall(r"(?m)^### [0-9]+\. ", interview)
        self.assertEqual(len(questions), 36)
        self.assertIn("undefined behavior", interview.lower())
        self.assertIn("100 points", assessment)
        self.assertIn("Non-negotiable safety gates", assessment)

    def test_all_local_markdown_links_resolve(self):
        # Verify relative links in both the preexisting and new written guides.
        for doc in ROOT.rglob("*.md"):
            for target in re.findall(r"\]\(([^)]+)\)", doc.read_text()):
                if target.startswith(("http:", "https:", "mailto:", "#")):
                    continue
                link_path = target.split("#", 1)[0].strip()
                if not link_path:
                    continue
                destination = (doc.parent / link_path).resolve()
                self.assertTrue(destination.exists(),
                                f"{doc.relative_to(ROOT)} -> {target}")

    def test_makefile_keeps_old_and_new_exercises_separate(self):
        make = (ROOT / "Makefile").read_text()
        for label in ("mastery-check", "mastery-reference",
                      "build/student", "build/reference",
                      "build/mastery-student", "build/mastery-reference"):
            self.assertIn(label, make)
        self.assertIn("foreach level", make)
        workflow = (ROOT / ".github/workflows/course.yml").read_text()
        self.assertIn("gcc, clang", workflow)
        self.assertIn("make reference", workflow)
        self.assertIn("make mastery-reference", workflow)


if __name__ == "__main__":
    unittest.main()
