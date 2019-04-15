/******************************************************************************
 *
 * Copyright (c) 2017, the Perspective Authors.
 *
 * This file is part of the Perspective library, distributed under the terms of
 * the Apache License 2.0.  The full license can be found in the LICENSE file.
 *
 */

const path = require("path");

const utils = require("@jpmorganchase/perspective-viewer/test/js/utils.js");
const simple_tests = require("@jpmorganchase/perspective-viewer/test/js/simple_tests.js");

const {withTemplate} = require("./simple-template");
withTemplate("line", "d3_y_line");

utils.with_server({}, () => {
    describe.page(
        "line.html",
        () => {
            simple_tests.default();
        },
        {reload_page: false, root: path.join(__dirname, "..", "..", "..")}
    );
});
