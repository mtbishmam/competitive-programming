// ==UserScript==
// @name         Hide Codeforces Problem Tags
// @namespace    https://codeforces.com/
// @version      1.0.0
// @description  Keep Codeforces problem tags hidden to avoid spoilers.
// @match        https://codeforces.com/*
// @match        https://*.codeforces.com/*
// @run-at       document-start
// @noframes
// @grant        none
// ==/UserScript==

(function () {
    'use strict';

    const hiddenClass = 'cf-hide-problem-tags';
    const tagLinkSelector = 'a[href*="/problemset?tags="], a[href*="/problemset?tags%3D"]';

    const style = document.createElement('style');
    style.textContent = `
        .${hiddenClass},
        .tag-box {
            display: none !important;
        }
    `;

    (document.head || document.documentElement).appendChild(style);

    function hideTags() {
        document.querySelectorAll('.tag-box').forEach((element) => {
            element.classList.add(hiddenClass);
        });

        document.querySelectorAll(tagLinkSelector).forEach((element) => {
            element.classList.add(hiddenClass);

            // On the problemset table, hide the whole right-aligned tag group
            // so that the remaining commas do not appear.
            if (element.parentElement) {
                element.parentElement.classList.add(hiddenClass);
            }
        });

        document.querySelectorAll('.sidebox .caption.titled').forEach((caption) => {
            if (/problem tags/i.test(caption.textContent || '')) {
                caption.closest('.sidebox')?.classList.add(hiddenClass);
            }
        });
    }

    hideTags();

    const observer = new MutationObserver(hideTags);
    observer.observe(document.documentElement, {
        childList: true,
        subtree: true,
    });
})();
