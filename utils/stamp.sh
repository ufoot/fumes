#!/bin/sh

# Fumes is a client implementation for Liquid War 7.
# Copyright (C)  2015  Christian Mauduit <ufoot@ufoot.org>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Fumes homepage: https://github.com/ufoot/fumes
# Contact author: ufoot@ufoot.org

if [ -d ../utils ] ; then
    cd ..
fi
if [ ! -d utils ] ; then
    echo "$0 should be run in srcdir"
    exit 1
fi

PACKAGE_TARNAME="fumes"
PACKAGE_NAME="Fumes Client"
PACKAGE_EMAIL="ufoot@ufoot.org"
PACKAGE_URL="https:\\/\\/github.com\\/ufoot\\/fumes"
VERSION_MAJOR=0
VERSION_MINOR=1

find_configure_ac () {
    if [ -f configure.ac ] ; then
	    CONFIGURE_AC="configure.ac"
	    if [ -f ${CONFIGURE_AC} ] ; then
            true
	    else
            echo "unable to open ${CONFIGURE_AC}"
            exit 2
	    fi
    else
	    echo "unable to find configure.ac"
	    exit 1
    fi
}

find_fmbuild_version_cpp () {
    if [ -f src/lib/fmbuild/fmbuild-version.cpp ] ; then
	    FMBUILD_VERSION_CPP="src/lib/fmbuild/fmbuild-version.cpp"
	    if [ -f ${CONFIGURE_AC} ] ; then
            true
	    else
            echo "unable to open ${FMBUILD_VERSION_CPP}"
            exit 2
	    fi
    else
	    echo "unable to find src/lib/fmbuild/fmbuild-version.cpp"
	    exit 1
    fi
}

find_fmbuild_package_cpp () {
    if [ -f src/lib/fmbuild/fmbuild-package.cpp ] ; then
	    FMBUILD_PACKAGE_CPP="src/lib/fmbuild/fmbuild-package.cpp"
	    if [ -f ${CONFIGURE_AC} ] ; then
            true
	    else
            echo "unable to open ${FMBUILD_PACKAGE_CPP}"
            exit 2
	    fi
    else
	    echo "unable to find src/lib/fmbuild/fmbuild-package.cpp"
	    exit 1
    fi
}

git_check () {
    if git status > /dev/null 2>&1 ; then
        true
    else
        echo "this is not a git repo, $0 won't do anything"
        exit 0
    fi
}

git_changelog () {
    if which git2cl > /dev/null ; then
        GIT_FILES=$(ls -d * | grep -v "ChangeLog" | sort | tr "\n" " ")
        git log --pretty --numstat --summary -- $GIT_FILES | git2cl > ChangeLog
    fi
}

calc_branch () {
    VERSION_BRANCH=$(git branch --color=never | grep "* " | cut -c 3- | sed "s/ //g")
    if [ "x${VERSION_BRANCH}" = "x" ] ; then
        VERSION_BRANCH=unknown
    fi
    if [ "x${VERSION_BRANCH}" = "xmaster" ] ; then
        VERSION_BRANCH=
    fi
}

calc_commits () {
    if [ "x${VERSION_BRANCH}" = "x" ] ; then
	SRC_CXX=$(ls -d src/lib/fm* | grep -v "fmbuild" | sort | tr "\n" " ")
	VERSION_COMMITS=$(git log --oneline --color=never -- ${SRC_CXX} | wc -l)
    else
	VERSION_COMMITS=
    fi
}

do_patch () {
    VERSION_STAMP=${VERSION_COMMITS}${VERSION_BRANCH}
    VERSION_DOT=${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_STAMP}
    if grep -q ${VERSION_DOT} ${CONFIGURE_AC} ; then
        echo "current version is ${VERSION_DOT}"
        #touch ${CONFIGURE_AC}
    else
        echo "patching ${FMBUILD_PACKAGE_CPP} with package tarname=${PACKAGE_TARNAME} name=${PACKAGE_NAME} email=${PACKAGE_EMAIL} url=${PACKAGE_URL}"
        sed -i "s/constexpr.*PACKAGE_TARNAME.*/constexpr char PACKAGE_TARNAME[] = \"${PACKAGE_TARNAME}\";/g" ${FMBUILD_PACKAGE_CPP}
        sed -i "s/constexpr.*PACKAGE_NAME.*/constexpr char PACKAGE_NAME[] = \"${PACKAGE_NAME}\";/g" ${FMBUILD_PACKAGE_CPP}
        sed -i "s/constexpr.*PACKAGE_EMAIL.*/constexpr char PACKAGE_EMAIL[] = \"${PACKAGE_EMAIL}\";/g" ${FMBUILD_PACKAGE_CPP}
        sed -i "s/constexpr.*PACKAGE_URL.*/constexpr char PACKAGE_URL[] = \"${PACKAGE_URL}\";/g" ${FMBUILD_PACKAGE_CPP}
        if which indent > /dev/null ; then indent ${FMBUILD_PACKAGE_CPP} ; fi
        if which indent > /dev/null ; then indent ${FMBUILD_PACKAGE_CPP} ; fi
        echo "patching ${FMBUILD_VERSION_CPP} with version major=${VERSION_MAJOR} minor=${VERSION_MINOR} stamp=${VERSION_STAMP}"
        sed -i "s/constexpr.*VERSION_MAJOR.*/constexpr int VERSION_MAJOR = ${VERSION_MAJOR};/g" ${FMBUILD_VERSION_CPP}
        sed -i "s/constexpr.*VERSION_MINOR.*/constexpr int VERSION_MINOR = ${VERSION_MINOR};/g" ${FMBUILD_VERSION_CPP}
        sed -i "s/constexpr.*VERSION_STAMP.*/constexpr char VERSION_STAMP[] = \"${VERSION_STAMP}\";/g" ${FMBUILD_VERSION_CPP}
        if which indent > /dev/null ; then indent ${FMBUILD_VERSION_CPP} ; fi
        if which indent > /dev/null ; then indent ${FMBUILD_VERSION_CPP} ; fi
        echo "patching ${CONFIGURE_AC} with version ${VERSION_DOT}"
        sed -i "s/^AC_INIT.*/AC_INIT([${PACKAGE_NAME}],[${VERSION_DOT}],[${PACKAGE_EMAIL}],[${PACKAGE_TARNAME}],[${PACKAGE_URL}])/g" ${CONFIGURE_AC}
        if which indent > /dev/null && test -x utils/indent.sh > /dev/null ; then utils/indent.sh ; fi
    fi
}

find_configure_ac
find_fmbuild_version_cpp
find_fmbuild_package_cpp
git_check
git_changelog
calc_branch
calc_commits
do_patch

