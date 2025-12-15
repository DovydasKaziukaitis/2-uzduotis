#include "pch.h"
#include "CppUnitTest.h"
#include "student9.h"
#include <vector>
#include <utility>
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(StudentasTests)
    {
    public:

        TEST_METHOD(DefaultConstructor)
        {
            Studentas st;

            Assert::IsTrue(st.getPavarde().empty());
            Assert::IsTrue(st.getVardas().empty());
            Assert::IsTrue(st.getNd().empty());

            Assert::AreEqual(0.0, st.getEgz());
            Assert::AreEqual(0.0, st.getGalVid());
            Assert::AreEqual(0.0, st.getGalMed());
        }

        TEST_METHOD(ParameterizedConstructor)
        {
            std::vector<double> nd = { 8, 9, 10 };
            double egz = 10.0;

            Studentas st("Pav", "Var", nd, egz);

            Assert::AreEqual(std::string("Pav"), st.getPavarde());
            Assert::AreEqual(std::string("Var"), st.getVardas());
            Assert::AreEqual((size_t)3, st.getNd().size());
            Assert::AreEqual(10.0, st.getEgz());

            Assert::IsTrue(std::abs(st.getGalVid() - 9.4) < 1e-9);
            Assert::IsTrue(std::abs(st.getGalMed() - 9.4) < 1e-9);
        }

        TEST_METHOD(CopyConstructor)
        {
            Studentas a("Pav", "Var", { 5, 6, 7, 8 }, 9.0);
            Studentas b(a);

            Assert::AreEqual(a.getPavarde(), b.getPavarde());
            Assert::AreEqual(a.getVardas(), b.getVardas());
            Assert::AreEqual(a.getNd().size(), b.getNd().size());

            Assert::AreEqual(a.getEgz(), b.getEgz());
            Assert::IsTrue(std::abs(a.getGalVid() - b.getGalVid()) < 1e-9);
            Assert::IsTrue(std::abs(a.getGalMed() - b.getGalMed()) < 1e-9);
        }

        TEST_METHOD(CopyAssignment)
        {
            Studentas a("A", "AA", { 10, 10, 10 }, 10.0);
            Studentas b("B", "BB", { 1, 2, 3 }, 1.0);

            b = a;

            Assert::AreEqual(a.getPavarde(), b.getPavarde());
            Assert::AreEqual(a.getVardas(), b.getVardas());
            Assert::AreEqual(a.getNd().size(), b.getNd().size());

            Assert::AreEqual(a.getEgz(), b.getEgz());
            Assert::IsTrue(std::abs(a.getGalVid() - b.getGalVid()) < 1e-9);
            Assert::IsTrue(std::abs(a.getGalMed() - b.getGalMed()) < 1e-9);
        }

        TEST_METHOD(MoveConstructor)
        {
            Studentas original("X", "Y", { 4, 5, 6 }, 7.0);

            auto pav = original.getPavarde();
            auto var = original.getVardas();
            auto gv = original.getGalVid();
            auto gm = original.getGalMed();

            Studentas moved(std::move(original));

            Assert::AreEqual(pav, moved.getPavarde());
            Assert::AreEqual(var, moved.getVardas());
            Assert::IsTrue(std::abs(gv - moved.getGalVid()) < 1e-9);
            Assert::IsTrue(std::abs(gm - moved.getGalMed()) < 1e-9);
        }

        TEST_METHOD(MoveAssignment)
        {
            Studentas src("X", "Y", { 9, 9, 9 }, 9.0);
            Studentas dst("A", "B", { 1, 2 }, 1.0);

            auto pav = src.getPavarde();
            auto var = src.getVardas();
            auto gv = src.getGalVid();
            auto gm = src.getGalMed();

            dst = std::move(src);

            Assert::AreEqual(pav, dst.getPavarde());
            Assert::AreEqual(var, dst.getVardas());
            Assert::IsTrue(std::abs(gv - dst.getGalVid()) < 1e-9);
            Assert::IsTrue(std::abs(gm - dst.getGalMed()) < 1e-9);
        }
    };
}

